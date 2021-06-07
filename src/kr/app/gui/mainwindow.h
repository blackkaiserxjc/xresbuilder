#pragma once

#include <QMainWindow>
#include <QSettings>

#include "config_options.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class CustomFileSystemModel;
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void OnActionOpenDataDir();

  void OnClickOpenServerDir();
  void OnClickOpenClientDir();
  void OnClickOpenLocalDir();

protected:
	void initUI();
  void initSignals();

  void loadConfig();
  void saveConfig();

  void closeEvent(QCloseEvent *event);

private:
  Ui::MainWindow *ui;
  CustomFileSystemModel *model_;
  QSettings settings_;
  ConfigOptions options_;
};
