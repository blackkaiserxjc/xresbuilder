#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initUI();

  // ÐÅºÅ²Û
  QObject::connect(ui->action, SIGNAL(triggered()), this,
                   SLOT(OnActionOpenDataDir()));

  QObject::connect(ui->server_btn, SIGNAL(clicked()), this,
                   SLOT(OnClickOpenServerDir()));

  QObject::connect(ui->client_btn, SIGNAL(clicked()), this,
                   SLOT(OnClickOpenClientDir()));

  QObject::connect(ui->local_btn, SIGNAL(clicked()), this,
                   SLOT(OnClickOpenLocalDir()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initUI()
{
	model = new FileSystemModel();
	model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

	ui->treeView->setModel(model);
	ui->treeView->header()->setStretchLastSection(true);
	ui->treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
	ui->treeView->header()->setSortIndicatorShown(true);
	ui->treeView->setEditTriggers(QTreeView::NoEditTriggers);
	ui->treeView->setSelectionBehavior(QTreeView::SelectRows);
	ui->treeView->setSelectionMode(QTreeView::SingleSelection);
	ui->treeView->setAlternatingRowColors(true);
	ui->treeView->setFocusPolicy(Qt::NoFocus);

	QModelIndex index = model->index(QDir::homePath());
	ui->treeView->setRootIndex(index);
	// ui->treeView->expand(index);
	// ui->treeView->scrollTo(index);
	ui->treeView->resizeColumnToContents(0);

	QMap<QString, int> cbData;
	cbData.insert("Lua", 1);
	cbData.insert("Json", 2);
	cbData.insert("C#", 3);

	foreach(const QString &text, cbData.keys())
		ui->server_cb->addItem(text, cbData.value(text));

	foreach(const QString &text, cbData.keys())
		ui->client_cb->addItem(text, cbData.value(text));

	foreach(const QString &text, cbData.keys())
		ui->local_cb->addItem(text, cbData.value(text));
}

void MainWindow::OnActionOpenDataDir() {
  qDebug() << "OnActionOpenDataDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  QModelIndex index = model->index(dir);
  ui->treeView->setRootIndex(index);
}

void MainWindow::OnClickOpenServerDir() {
  qDebug() << "OnClickOpenServerDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  ui->server_edit->setText(dir);
}

void MainWindow::OnClickOpenClientDir() {
  qDebug() << "OnClickOpenClientDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  ui->client_edit->setText(dir);
}

void MainWindow::OnClickOpenLocalDir() {
  qDebug() << "OnClickOpenLocalDir";
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  ui->local_edit->setText(dir);
}
