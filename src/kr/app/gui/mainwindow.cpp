#include "mainwindow.h"
#include "QsLog.h"
#include "fsmodel.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      settings_("config.ini", QSettings::IniFormat), model_(new FSModel()) {
  ui->setupUi(this);
  loadConfig();
  initUI();
  initSignals();
}

MainWindow::~MainWindow() {
  delete model_;
  delete ui;
}

void MainWindow::Log(const QString &message, int level) {
  using namespace QsLogging;
  switch (level) {
  case TraceLevel:
  case DebugLevel:
  case InfoLevel:
	  ui->logView->appendHtml(QLatin1String("<pre>") + message.toHtmlEscaped() +
		                                 QLatin1String("</pre>"));
    break;
  case WarnLevel:
	  ui->logView->appendHtml(QLatin1String("<pre style='color:orange'>") + message.toHtmlEscaped() + QLatin1String("</pre>"));
    break;
  case ErrorLevel:
  case FatalLevel:
	  ui->logView->appendHtml(QLatin1String("<pre style='color:red'>") + message.toHtmlEscaped() + QLatin1String("</pre>"));
    break;
  }

  /*
QTextCursor prev_cursor = ui->logView->textCursor();
ui->logView->moveCursor(QTextCursor::End);
ui->logView->insertPlainText(message + tr("\n"));
ui->logView->setTextCursor(prev_cursor);
*/
}

void MainWindow::closeEvent(QCloseEvent *event) {
  qDebug() << "MainWindow::closeEvent";
  saveConfig();
  event->accept();
}

void MainWindow::initUI() {
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

  QMap<QString, int> cbData;
  cbData.insert("Lua", 1);
  cbData.insert("Json", 2);
  cbData.insert("C#", 3);
  foreach (const QString &text, cbData.keys())
    ui->server_cb->addItem(text, cbData.value(text));
  foreach (const QString &text, cbData.keys())
    ui->client_cb->addItem(text, cbData.value(text));
  foreach (const QString &text, cbData.keys())
    ui->local_cb->addItem(text, cbData.value(text));

  ui->server_edit->setText(options_.gen_server_path);
  ui->client_edit->setText(options_.gen_client_path);
  ui->local_edit->setText(options_.gen_local_path);
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
  ui->server_edit->setText(dir);
  options_.gen_server_path = dir;
}

void MainWindow::OnClickOpenClientDir() {
  qDebug() << "OnClickOpenClientDir";
  QLOG_ERROR() << "OnClickOpenClientDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  ui->client_edit->setText(dir);
  options_.gen_client_path = dir;
}

void MainWindow::OnClickOpenLocalDir() {
  qDebug() << "OnClickOpenLocalDir";
  QLOG_DEBUG() << "OnClickOpenLocalDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  ui->local_edit->setText(dir);
  options_.gen_local_path = dir;

  QList<QPersistentModelIndex> indexList = model_->checkedIndexes();
  for (const QPersistentModelIndex &index : indexList)
    qDebug() << model_->filePath(index);
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
