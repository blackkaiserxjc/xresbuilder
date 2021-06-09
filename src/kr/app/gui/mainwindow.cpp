#include "mainwindow.h"
#include "QsLog.h"
#include "fsmodel.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QVBoxLayout>

Worker::Worker(QObject *parent)
{
}

Worker::~Worker()
{
}

void Worker::doWork(WorkerParam param)
{
    QLOG_DEBUG() << "receive the execute signal" ;
    QLOG_DEBUG() << "\tCurrent thread ID: " << QThread::currentThreadId();
    QLOG_DEBUG() << "\tFinish the work and sent the result Ready signal\n" ;
    QLOG_DEBUG() << "data_path:" << param.options.data_path;
    QLOG_DEBUG() << "gen_server_path:" << param.options.gen_server_path;

    for(auto&& path: param.paths)
    {
      QLOG_DEBUG() << "path:" << path;
    }
    emit resultReady(0);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      settings_("config.ini", QSettings::IniFormat), model_(new FSModel()) {
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

  QMap<QString, int> cbData = {
    {"Lua", GenLanguageType::LUA},
    {"Json", GenLanguageType::JSON},
    {"C#", GenLanguageType::CSHARP}
  };
  for (auto iter = cbData.begin(); iter != cbData.end(); iter++)
  {
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
    ui->logView->appendHtml(QLatin1String("<pre style='color:green'>") + message.toHtmlEscaped() +
                            QLatin1String("</pre>"));
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
    qDebug() << "receive the resultReady signal" ;
    qDebug() << "\tCurrent thread ID: " << QThread::currentThreadId() << '\n' ;
    qDebug() << "\tThe last result is: " << result;
}

void MainWindow::OnActionOpenDataDir() {
  qDebug() << "OnActionOpenDataDir";
  QLOG_DEBUG() << "OnActionOpenDataDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  QModelIndex index = model_->index(dir);
  ui->treeView->setRootIndex(index);
  options_.data_path = dir;
  model_->reset();
}

void MainWindow::OnClickOpenServerDir() {
  qDebug() << "OnClickOpenServerDir";
  QLOG_WARN() << "OnClickOpenServerDir";
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
  QLOG_ERROR() << "OnClickOpenClientDir";
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
  QLOG_DEBUG() << "OnClickOpenLocalDir";
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
  if (indexList.empty()) {
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

  emit startWork(param);
}

void MainWindow::loadConfig() {
  options_.data_path = settings_.value("data_path").toString();
  options_.gen_server_path = settings_.value("gen_server_path").toString();
  options_.gen_client_path = settings_.value("gen_client_path").toString();
  options_.gen_local_path = settings_.value("gen_local_path").toString();
  options_.name_filters = settings_.value("name_filters").toString();
}

void MainWindow::saveConfig() {
  settings_.setValue("data_path", options_.data_path);
  settings_.setValue("gen_server_path", options_.gen_server_path);
  settings_.setValue("gen_client_path", options_.gen_client_path);
  settings_.setValue("gen_local_path", options_.gen_local_path);
}
