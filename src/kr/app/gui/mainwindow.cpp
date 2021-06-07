#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    QModelIndex index = model->index(QString("./"));
    ui->treeView->setRootIndex(index);
    //ui->treeView->expand(index);
    //ui->treeView->scrollTo(index);
    ui->treeView->resizeColumnToContents(0);
    QObject::connect(ui->pushButton ,SIGNAL(clicked()),this,SLOT(PushButtonCallBack()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PushButtonCallBack()
{
    qDebug() << "PushButtonCallBack";
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QModelIndex index = model->index(dir);
    ui->treeView->setRootIndex(index);
}

