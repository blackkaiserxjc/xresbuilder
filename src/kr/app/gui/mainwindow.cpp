#include <memory>

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>

#include "QsLog.h"
#include "fsmodel.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

static void CompilerDebug(const std::string &debug_msg) {
  QLOG_DEBUG() << debug_msg.c_str();
}

static void CompilerWarning(const std::string &warn_msg) {
  QLOG_WARN() << warn_msg.c_str();
}

static void CompilerError(const std::string &error_msg) {
  QLOG_ERROR() << error_msg.c_str();
}

Worker::Worker(QObject *parent) {}

Worker::~Worker() {}

void Worker::doWork(WorkerParam param) {
  using namespace kr::core;
  if (param.options.data_path.isEmpty() || !param.paths.length()) {
    emit resultReady(1);
    return;
  }

  const Compiler::Generator generators[] = {
      {generate_json, "json", "Json", IDLOptions::kJson,
       "Generate Json schema"},
      {generate_lua, "lua", "Lua", IDLOptions::kLua, "Generate Lua files"},
      {generate_csharp, "csharp", "C#", IDLOptions::kCSharp,
       "Generate C# class"}};
  Compiler::InitParams init_params;
  init_params.generators = generators;
  init_params.num_generators = sizeof(generators) / sizeof(generators[0]);
  init_params.warn_fn = CompilerWarning;
  init_params.error_fn = CompilerError;
  init_params.debug_fn = CompilerDebug;
  Compiler compiler(init_params);

  auto is_vaild_path = [](auto &&path, auto &&type) {
    return !path.isEmpty() && type != 0;
  };

  auto convert_gen_type = [](auto &&type) {
    if (type == GenLanguageType::LUA)
      return static_cast<int>(IDLOptions::kLua);
    else if (type == GenLanguageType::JSON)
      return static_cast<int>(IDLOptions::kJson);
    else if (type == GenLanguageType::CSHARP)
      return static_cast<int>(IDLOptions::kCSharp);
    else
      return 0;
  };

  IDLOptions options;
  options.src = param.options.data_path.toStdString();
  for (auto &&p : param.paths) {
    options.src_paths_.emplace_back(p.toStdString());
  }

  if (is_vaild_path(param.options.gen_server_path,
                    param.options.gen_server_type)) {
    options.dest = param.options.gen_server_path.toStdString();
    options.lang_to_generate = convert_gen_type(param.options.gen_server_type);
    compiler.run_with_gui(options);
  }
  if (is_vaild_path(param.options.gen_client_path,
                    param.options.gen_client_type)) {
    options.dest = param.options.gen_client_path.toStdString();
    options.lang_to_generate = convert_gen_type(param.options.gen_client_type);
    compiler.run_with_gui(options);
  }
  if (is_vaild_path(param.options.gen_local_path,
                    param.options.gen_local_type)) {
    options.dest = param.options.gen_local_path.toStdString();
    options.lang_to_generate = convert_gen_type(param.options.gen_local_type);
    compiler.run_with_gui(options);
  }
  emit resultReady(0);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      settings_("config.ini", QSettings::IniFormat), model_(new FSModel()),
      svn_model_(new SvnModel()) {
  ui->setupUi(this);
  loadConfig();
  initUI();
  initSignals();
  initThreads();
}

MainWindow::~MainWindow() {
  work_thread_->quit();
  work_thread_->wait();
  delete model_;
  delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
  qDebug() << "MainWindow::closeEvent";
  saveConfig();
  event->accept();
}

void MainWindow::initUI() {
  setWindowTitle(QLatin1String("XResBuilder"));

  QStringList filters = options_.name_filters.split("|");
  qDebug() << filters;
  model_->setRootPath(QDir::rootPath());
  model_->setNameFilters(filters);
  model_->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);

  ui->treeView->setModel(model_);
  ui->treeView->header()->setStretchLastSection(true);
  ui->treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
  ui->treeView->header()->setSortIndicatorShown(true);
  ui->treeView->setEditTriggers(QTreeView::NoEditTriggers);
  ui->treeView->setSelectionBehavior(QTreeView::SelectRows);
  ui->treeView->setSelectionMode(QTreeView::SingleSelection);
  ui->treeView->setAlternatingRowColors(true);
  ui->treeView->setFocusPolicy(Qt::NoFocus);
  ui->treeView->setColumnHidden(1, true);
  ui->treeView->setColumnHidden(2, true);
  ui->treeView->setColumnHidden(3, true);
  QModelIndex index = model_->index(
      options_.data_path.isEmpty() ? QDir::homePath() : options_.data_path);
  ui->treeView->setRootIndex(index);
  ui->treeView->resizeColumnToContents(0);

  ui->svnView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->svnView->horizontalHeader()->setStretchLastSection(true);
  ui->svnView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->svnView->horizontalHeader()->setHighlightSections(false);
  ui->svnView->verticalHeader()->setVisible(false);
  ui->svnView->setShowGrid(false);
  ui->svnView->setFrameShape(QFrame::NoFrame);
  ui->svnView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->svnView->setModel(svn_model_);

  QMap<QString, int> cbData = {{"Lua", GenLanguageType::LUA},
                               {"Json", GenLanguageType::JSON},
                               {"C#", GenLanguageType::CSHARP}};
  for (auto iter = cbData.begin(); iter != cbData.end(); iter++) {
    ui->server_cb->addItem(iter.key(), iter.value());
    ui->client_cb->addItem(iter.key(), iter.value());
    ui->local_cb->addItem(iter.key(), iter.value());
  }

  ui->server_edit->setText(options_.gen_server_path);
  ui->client_edit->setText(options_.gen_client_path);
  ui->local_edit->setText(options_.gen_local_path);
}

void MainWindow::initThreads() {
  // 注册参数类型
  qRegisterMetaType<WorkerParam>("WorkerParam");
  // 线程初始化
  work_thread_ = new QThread();
  auto worker = new Worker();
  worker->moveToThread(work_thread_);

  // 启动工作
  connect(this, SIGNAL(startWork(WorkerParam)), worker,
          SLOT(doWork(WorkerParam)));
  // 线程销毁结束时销毁
  connect(work_thread_, &QThread::finished, worker, &QObject::deleteLater);
  // 线程结束，处理结果
  connect(worker, SIGNAL(resultReady(int)), this, SLOT(HandleResult(int)));
  // 启动线程
  work_thread_->start();
}

void MainWindow::initSignals() {

  // 信号槽
  QObject::connect(ui->action, SIGNAL(triggered()), this,
                   SLOT(OnActionOpenDataDir()));

  QObject::connect(ui->server_btn, SIGNAL(clicked()), this,
                   SLOT(OnClickOpenServerDir()));

  QObject::connect(ui->client_btn, SIGNAL(clicked()), this,
                   SLOT(OnClickOpenClientDir()));

  QObject::connect(ui->local_btn, SIGNAL(clicked()), this,
                   SLOT(OnClickOpenLocalDir()));

  QObject::connect(ui->export_btn, SIGNAL(clicked()), this,
                   SLOT(OnClickExportConfig()));
}

void MainWindow::Log(const QString &message, int level) {
  using namespace QsLogging;
  switch (level) {
  case TraceLevel:
  case DebugLevel:
  case InfoLevel:
    ui->logView->appendHtml(QLatin1String("<pre style='color:green'>") +
                            message.toHtmlEscaped() + QLatin1String("</pre>"));
    break;
  case WarnLevel:
    ui->logView->appendHtml(QLatin1String("<pre style='color:orange'>") +
                            message.toHtmlEscaped() + QLatin1String("</pre>"));
    break;
  case ErrorLevel:
  case FatalLevel:
    ui->logView->appendHtml(QLatin1String("<pre style='color:red'>") +
                            message.toHtmlEscaped() + QLatin1String("</pre>"));
    break;
  }
}

void MainWindow::HandleResult(int result) {
  qDebug() << "receive the resultReady signal";
  qDebug() << "\tCurrent thread ID: " << QThread::currentThreadId() << '\n';
  qDebug() << "\tThe last result is: " << result;

  ui->export_btn->setEnabled(true);
}

void MainWindow::OnActionOpenDataDir() {
  qDebug() << "OnActionOpenDataDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  QModelIndex index = model_->index(dir);
  ui->treeView->setRootIndex(index);
  options_.data_path = dir;
  model_->reset();
  loadSvnData(dir);
}

void MainWindow::OnClickOpenServerDir() {
  qDebug() << "OnClickOpenServerDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir.isEmpty()) {
    ui->server_edit->setText(dir);
    options_.gen_server_path = dir;
  }
}

void MainWindow::OnClickOpenClientDir() {
  qDebug() << "OnClickOpenClientDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!dir.isEmpty()) {
    ui->client_edit->setText(dir);
    options_.gen_client_path = dir;
  }
}

void MainWindow::OnClickOpenLocalDir() {
  qDebug() << "OnClickOpenLocalDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir.isEmpty()) {
    ui->local_edit->setText(dir);
    options_.gen_local_path = dir;
  }
}

void MainWindow::OnClickExportConfig() {
  qDebug() << "OnClickExportConfig";

  auto indexList = model_->checkedIndexes();
  auto svnRecords = svn_model_->records();
  if (indexList.count() == 0 && svnRecords.count() == 0) {
    QMessageBox::warning(NULL, "warning", tr("no select files or dirs."),
                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    return;
  }

  WorkerParam param;
  options_.gen_server_type =
      ui->server_cb->itemData(ui->server_cb->currentIndex()).toInt();
  options_.gen_client_type =
      ui->client_cb->itemData(ui->client_cb->currentIndex()).toInt();
  options_.gen_local_type =
      ui->local_cb->itemData(ui->local_cb->currentIndex()).toInt();
  param.options = options_;
  for (const QPersistentModelIndex &index : indexList) {
    param.paths.push_back(model_->filePath(index));
  }
  for (auto &record : svnRecords) {
    if (record.check) {
      param.paths.push_back(record.file_path);
	  qDebug() << record.file_path;
    }
  }

  
  ui->export_btn->setDisabled(true);
  emit startWork(param);
}

void MainWindow::loadConfig() {
  options_.data_path = settings_.value("data_path").toString();
  options_.gen_server_path = settings_.value("gen_server_path").toString();
  options_.gen_client_path = settings_.value("gen_client_path").toString();
  options_.gen_local_path = settings_.value("gen_local_path").toString();
  options_.name_filters = settings_.value("name_filters").toString();
  options_.log_level = settings_.value("log_level").toInt();
  auto &logger = QsLogging::Logger::instance();
  if (options_.log_level != 0) {
    logger.setLoggingLevel(static_cast<QsLogging::Level>(options_.log_level));
  }
}

void MainWindow::saveConfig() {
  settings_.setValue("data_path", options_.data_path);
  settings_.setValue("gen_server_path", options_.gen_server_path);
  settings_.setValue("gen_client_path", options_.gen_client_path);
  settings_.setValue("gen_local_path", options_.gen_local_path);
}

void MainWindow::loadSvnData(const QString &path) {
  auto process = std::make_shared<QProcess>();
  process->start("svn", QStringList() << "diff" << path << "--summarize");
  process->waitForFinished();
  QString buffer = process->readAll();
  QStringList svnList = buffer.split(QRegExp("\\s+"), QString::SkipEmptyParts);
  qDebug() << "svn diff list: " << svnList;

  QList<SvnRecord> records;
  if (svnList.count() == 0) {
    QLOG_ERROR() << "svn diff list is zero:" << path;
    svn_model_->updateData(records);
    return;
  }

  if (svnList.count() & 0x01) {
    QLOG_ERROR() << "invaild svn dir:" << path;
    svn_model_->updateData(records);
    return;
  }
  for (int index = 0; index < svnList.count(); index += 2) {
    auto &file_status = svnList[index];
    auto &file_path = svnList[index + 1];
    QFileInfo file(file_path);
    if (file.exists()) {
      SvnRecord record;
      record.check = false;
      record.file_path = file_path;
      record.file_ext = file.suffix();
      record.status = file_status;
      records.append(record);
    }
  }
  svn_model_->updateData(records);
}
