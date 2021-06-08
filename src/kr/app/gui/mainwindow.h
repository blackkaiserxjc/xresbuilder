#pragma once

#include <QMainWindow>
#include <QSettings>

#include "config_options.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class FSModel;
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void closeEvent(QCloseEvent *event);

public slots:
  void Log(const QString &message, int level);
  void OnActionOpenDataDir();
  void OnClickOpenServerDir();
  void OnClickOpenClientDir();
  void OnClickOpenLocalDir();

protected:
  void initUI();
  void initSignals();

  void loadConfig();
  void saveConfig();

private:
  Ui::MainWindow *ui;
  FSModel *model_;
  QSettings settings_;
  ConfigOptions options_;
};
