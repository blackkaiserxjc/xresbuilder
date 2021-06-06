#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new FileSystemModel();
    //model->setRootPath("/home/kaiser");
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

    QModelIndex index = model->index(QDir::currentPath());
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->resizeColumnToContents(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

