#pragma once

#include <QMainWindow>
#include <QSettings>
#include <QThread>

#include "config_options.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class FSModel;
struct WorkerParam
{
  WorkerParam() : options{}, paths{}
  {}

  ConfigOptions options;
  QVector<QString> paths;
};
class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QObject *parent = nullptr);
    ~Worker();

public slots:
    void doWork(WorkerParam param);
signals:
    void resultReady(int result);
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void closeEvent(QCloseEvent *event);

public slots:
  void Log(const QString &message, int level);
  void HandleResult(int result);
  void OnActionOpenDataDir();
  void OnClickOpenServerDir();
  void OnClickOpenClientDir();
  void OnClickOpenLocalDir();
  void OnClickExportConfig();
signals:
  void startWork(WorkerParam param);

protected:
  void initUI();
  void initThreads();
  void initSignals();

  void loadConfig();
  void saveConfig();
private:
  Ui::MainWindow *ui;
  FSModel *model_;
  QSettings settings_;
  ConfigOptions options_;
  QThread *work_thread_;
};
