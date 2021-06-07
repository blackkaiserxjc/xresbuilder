#pragma once

#include "filesystem_model.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void OnActionOpenDataDir();

  void OnClickOpenServerDir();
  void OnClickOpenClientDir();
  void OnClickOpenLocalDir();

protected:
	void initUI();

private:
  Ui::MainWindow *ui;
  FileSystemModel *model;
};
