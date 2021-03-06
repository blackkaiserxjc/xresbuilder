#include <filesystem>
#include <fmt/format.h>
#include <map>
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

namespace fs = std::filesystem;

static void CompilerDebug(const std::string &debug_msg)
{
    QLOG_DEBUG() << QString::fromLocal8Bit(debug_msg.c_str());
}

static void CompilerWarning(const std::string &warn_msg)
{
    QLOG_WARN() << QString::fromLocal8Bit(warn_msg.c_str());
}

static void CompilerError(const std::string &error_msg)
{
    QLOG_ERROR() << QString::fromLocal8Bit(error_msg.c_str());
}

Worker::Worker(QObject *parent)
{
}

Worker::~Worker()
{
}

void Worker::doWork(WorkerParam param)
{
    using namespace kr::core;
    if (param.options.data_path.isEmpty() || !param.paths.length())
    {
        emit resultReady(1);
        return;
    }

    std::vector<std::string> full_paths;
    for (auto &&p : param.paths)
    {
        std::string str = p.toLocal8Bit().data();
        if (fs::is_regular_file(str))
        {
            full_paths.emplace_back(str);
        }
        else if (fs::is_directory(str))
        {
            for (auto &entry : fs::recursive_directory_iterator(str))
            {
                if (entry.is_regular_file())
                {
                    full_paths.emplace_back(entry.path().string());
                }
            }
        }
    }

    std::map<std::string, std::string> path_map;
    fs::path xm_root_path(
        std::string(param.options.data_path.toLocal8Bit().data()));
    fs::path csv_root_path(
        std::string(param.options.csv_tmp_path.toLocal8Bit().data()));
    fs::remove_all(csv_root_path);
    for (auto &&p : full_paths)
    {
        fs::path xm_path(p);
        auto relative_path = fs::relative(xm_path, xm_root_path);
        auto target_path = csv_root_path;
        target_path /= relative_path;
        auto parent_path = target_path.parent_path();
        if (!fs::exists(parent_path))
        {
            fs::create_directories(parent_path);
        }
        auto target_path_str =
            fmt::format("{}/{}.csv", target_path.parent_path().string(),
                xm_path.stem().string());
        path_map.emplace(xm_path.string(), target_path_str);
    }

    auto gen_relative_path = [](auto &&root, auto &&p) {
        fs::path cur_path(p);
        auto relative_path = fs::relative(cur_path, root);
        return relative_path.string();
    };

    for (auto &&[key, value] : path_map)
    {
        auto src_path =
            QDir::fromNativeSeparators(QString::fromLocal8Bit(key.data()));
        auto dest_path =
            QDir::fromNativeSeparators(QString::fromLocal8Bit(value.data()));
        auto src_rel_path = gen_relative_path(xm_root_path, key);
        auto dest_rel_path = gen_relative_path(csv_root_path, value);
        auto process = std::make_shared<QProcess>();
        process->start("xlsx2csv", QStringList() << src_path << dest_path);
        process->waitForFinished();
        QLOG_INFO() << "convert"
                    << QDir::fromNativeSeparators(
                           QString::fromLocal8Bit(src_rel_path.data()))
                    << "to"
                    << QDir::fromNativeSeparators(
                           QString::fromLocal8Bit(dest_rel_path.data()));
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

    auto naming_style_rule = [](auto &&options) {
        if (options.lang_to_generate == IDLOptions::kCSharp)
        {
            options.filename_naming_style = IDLOptions::kPascalCase;
            options.folder_naming_style = IDLOptions::kPascalCase;
        }
        else if (options.lang_to_generate == IDLOptions::kJson)
        {
            options.filename_naming_style = IDLOptions::kPascalCase;
            options.folder_naming_style = 0;
        }
        else if (options.lang_to_generate == IDLOptions::kLua)
        {
            options.filename_naming_style = 0;
            options.folder_naming_style = 0;
        }
    };

    IDLOptions options;
    options.src = param.options.csv_tmp_path.toLocal8Bit().data();
    options.src_paths_.emplace_back(
        param.options.csv_tmp_path.toLocal8Bit().data());

    if (is_vaild_path(param.options.gen_server_path,
            param.options.gen_server_type))
    {
        options.dest = param.options.gen_server_path.toLocal8Bit().data();
        options.lang_to_generate = convert_gen_type(param.options.gen_server_type);
        naming_style_rule(options);
        QLOG_INFO()
            << "======================ServerConfig===============================";
        compiler.run_with_gui(options);
        QLOG_INFO() << "==========================================================="
                       "======\n";
    }
    if (is_vaild_path(param.options.gen_client_path,
            param.options.gen_client_type))
    {
        options.dest = param.options.gen_client_path.toLocal8Bit().data();
        options.lang_to_generate = convert_gen_type(param.options.gen_client_type);
        naming_style_rule(options);
        QLOG_INFO()
            << "======================ClientConfig===============================";
        compiler.run_with_gui(options);
        QLOG_INFO() << "==========================================================="
                       "======\n";
    }
    if (is_vaild_path(param.options.gen_local_path,
            param.options.gen_local_type))
    {
        options.dest = param.options.gen_local_path.toLocal8Bit().data();
        options.lang_to_generate = convert_gen_type(param.options.gen_local_type);
        naming_style_rule(options);
        QLOG_INFO()
            << "======================LocalConfig===============================";
        compiler.run_with_gui(options);
        QLOG_INFO() << "==========================================================="
                       "======\n";
    }
    emit resultReady(0);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), settings_("config.ini", QSettings::IniFormat), model_(new FSModel()), svn_model_(new SvnModel())
{
    ui->setupUi(this);
    loadConfig();
    initUI();
    initSignals();
    initThreads();
}

MainWindow::~MainWindow()
{
    work_thread_->quit();
    work_thread_->wait();
    delete svn_model_;
    delete model_;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow::closeEvent";
    updateComBoxIndexs();
    saveConfig();
    event->accept();
}

void MainWindow::initUI()
{
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
    for (auto iter = cbData.begin(); iter != cbData.end(); iter++)
    {
        ui->server_cb->addItem(iter.key(), iter.value());
        ui->client_cb->addItem(iter.key(), iter.value());
        ui->local_cb->addItem(iter.key(), iter.value());
    }

    if (auto scb_index = ui->server_cb->findData(
            options_.gen_server_type, Qt::UserRole, Qt::MatchCaseSensitive);
        scb_index >= 0)
    {
        ui->server_cb->setCurrentIndex(scb_index);
    }
    if (auto ccb_index = ui->client_cb->findData(
            options_.gen_client_type, Qt::UserRole, Qt::MatchCaseSensitive);
        ccb_index >= 0)
    {
        ui->client_cb->setCurrentIndex(ccb_index);
    }
    if (auto lcb_index = ui->local_cb->findData(
            options_.gen_local_type, Qt::UserRole, Qt::MatchCaseSensitive);
        lcb_index >= 0)
    {
        ui->local_cb->setCurrentIndex(lcb_index);
    }

    ui->server_edit->setText(options_.gen_server_path);
    ui->client_edit->setText(options_.gen_client_path);
    ui->local_edit->setText(options_.gen_local_path);

    setWindowState(Qt::WindowMaximized);

    refreshSvnModel();
}

void MainWindow::refreshSvnModel()
{
    auto process = std::make_shared<QProcess>();
    process->start("svn", QStringList() << "diff" << options_.data_path << "--summarize");
    process->waitForFinished();
    QString buffer =
        QString::fromLocal8Bit(process->readAllStandardOutput().data()).trimmed();
    QStringList svnList = buffer.split(QRegExp("\\s+"));
    qDebug() << "svn diff list: " << svnList;

    QList<SvnRecord> records;
    if (svnList.count() == 0)
    {
        QLOG_ERROR() << "svn diff list is zero:" << options_.data_path;
        svn_model_->updateData(records);
        return;
    }

    if (svnList.count() & 0x01)
    {
        QLOG_ERROR() << "invaild svn dir:" << options_.data_path;
        svn_model_->updateData(records);
        return;
    }
    for (int index = 0; index < svnList.count(); index += 2)
    {
        auto &file_status = svnList[index];
        auto file_path = QDir::fromNativeSeparators(svnList[index + 1]);
        QFileInfo file(file_path);
        if (file.exists())
        {
            SvnRecord record;
            record.check = true;
            record.file_path = file_path;
            record.file_ext = file.suffix();
            record.status = file_status;
            records.append(record);
        }
    }
    svn_model_->updateData(records);
}

void MainWindow::initThreads()
{
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

void MainWindow::initSignals()
{
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
    QObject::connect(ui->refresh_svn_btn, SIGNAL(clicked()), this,
        SLOT(OnClickRefreshSVN()));

    QObject::connect(ui->server_edit, &QLineEdit::textChanged, [this](QString arg) {
        options_.gen_server_path = arg;
    });
    QObject::connect(ui->client_edit, &QLineEdit::textChanged, [this](QString arg) {
        options_.gen_client_path = arg;
    });
    QObject::connect(ui->local_edit, &QLineEdit::textChanged, [this](QString arg) {
        options_.gen_local_path = arg;
    });
}

void MainWindow::Log(const QString &message, int level)
{
    using namespace QsLogging;
    switch (level)
    {
    case TraceLevel:
    case DebugLevel:
        ui->logView->appendHtml(QLatin1String("<pre style='color:lightgray'>") + message.toHtmlEscaped() + QLatin1String("</pre>"));
        break;
    case InfoLevel:
        ui->logView->appendHtml(QLatin1String("<pre style='color:#22DDDD'>") + message.toHtmlEscaped() + QLatin1String("</pre>"));
        break;
    case WarnLevel:
        ui->logView->appendHtml(QLatin1String("<pre style='color:orange'>") + message.toHtmlEscaped() + QLatin1String("</pre>"));
        break;
    case ErrorLevel:
    case FatalLevel:
        ui->logView->appendHtml(QLatin1String("<pre style='color:red'>") + message.toHtmlEscaped() + QLatin1String("</pre>"));
        break;
    }
}

void MainWindow::HandleResult(int result)
{
    qDebug() << "receive the resultReady signal";
    qDebug() << "\tCurrent thread ID: " << QThread::currentThreadId() << '\n';
    qDebug() << "\tThe last result is: " << result;

    ui->export_btn->setEnabled(true);
}

void MainWindow::OnActionOpenDataDir()
{
    qDebug() << "OnActionOpenDataDir";
    QString dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        QModelIndex index = model_->index(dir);
        ui->treeView->setRootIndex(index);
        options_.data_path = dir;
        model_->reset();
        refreshSvnModel();
    }
}

void MainWindow::OnClickOpenServerDir()
{
    qDebug() << "OnClickOpenServerDir";
    QString dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty())
    {
        ui->server_edit->setText(dir);
        options_.gen_server_path = dir;
    }
}

void MainWindow::OnClickOpenClientDir()
{
    qDebug() << "OnClickOpenClientDir";
    QString dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        ui->client_edit->setText(dir);
        options_.gen_client_path = dir;
    }
}

void MainWindow::OnClickOpenLocalDir()
{
    qDebug() << "OnClickOpenLocalDir";
    QString dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->local_edit->setText(dir);
    options_.gen_local_path = dir;
}

void MainWindow::OnClickExportConfig()
{
    qDebug() << "OnClickExportConfig";

    auto indexList = model_->checkedIndexes();
    auto svnRecords = svn_model_->records();
    if (indexList.count() == 0 && svnRecords.count() == 0)
    {
        QMessageBox::warning(NULL, "warning", tr("no select files or dirs."),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        return;
    }

    ui->logView->setPlainText("");

    WorkerParam param;
    options_.gen_server_type =
        ui->server_cb->itemData(ui->server_cb->currentIndex()).toInt();
    options_.gen_client_type =
        ui->client_cb->itemData(ui->client_cb->currentIndex()).toInt();
    options_.gen_local_type =
        ui->local_cb->itemData(ui->local_cb->currentIndex()).toInt();
    param.options = options_;
    for (const QPersistentModelIndex &index : indexList)
    {
        param.paths.push_back(model_->filePath(index));
    }
    for (auto &record : svnRecords)
    {
        if (record.check)
        {
            param.paths.push_back(record.file_path);
            qDebug() << record.file_path;
        }
    }
    ui->export_btn->setDisabled(true);
    emit startWork(param);
}

void MainWindow::OnClickRefreshSVN()
{
    refreshSvnModel();
}

void MainWindow::loadConfig()
{
    settings_.setIniCodec("UTF8");
    options_.log_level = settings_.value("log_level").toInt();
    options_.data_path = settings_.value("data_path").toString();
    options_.csv_tmp_path = settings_.value("csv_tmp_path").toString();
    options_.gen_server_path = settings_.value("gen_server_path").toString();
    options_.gen_server_type = settings_.value("gen_server_type").toInt();
    options_.gen_client_path = settings_.value("gen_client_path").toString();
    options_.gen_client_type = settings_.value("gen_client_type").toInt();
    options_.gen_local_path = settings_.value("gen_local_path").toString();
    options_.gen_local_type = settings_.value("gen_local_type").toInt();
    options_.name_filters = settings_.value("name_filters").toString();
    auto &logger = QsLogging::Logger::instance();
    if (options_.log_level != 0)
    {
        logger.setLoggingLevel(static_cast<QsLogging::Level>(options_.log_level));
    }
}

void MainWindow::saveConfig()
{
    settings_.setValue("data_path", options_.data_path);
    settings_.setValue("gen_server_path", options_.gen_server_path);
    settings_.setValue("gen_server_type", options_.gen_server_type);
    settings_.setValue("gen_client_path", options_.gen_client_path);
    settings_.setValue("gen_client_type", options_.gen_client_type);
    settings_.setValue("gen_local_path", options_.gen_local_path);
    settings_.setValue("gen_local_type", options_.gen_local_type);
}

void MainWindow::updateComBoxIndexs()
{
    options_.gen_server_type =
        ui->server_cb->itemData(ui->server_cb->currentIndex()).toInt();
    options_.gen_client_type =
        ui->client_cb->itemData(ui->client_cb->currentIndex()).toInt();
    options_.gen_local_type =
        ui->local_cb->itemData(ui->local_cb->currentIndex()).toInt();
}