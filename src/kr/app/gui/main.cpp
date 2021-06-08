
#include <kr/core/compiler.h>

#include <QApplication>

#include "QsLog.h"
#include "dark_style.h"
#include "framelesswindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  app.setApplicationName("XResBuilder");
  QApplication::setStyle(new DarkStyle);
  QApplication::setPalette(QApplication::style()->standardPalette());

  auto &logger = QsLogging::Logger::instance();
  logger.setLoggingLevel(QsLogging::TraceLevel);

  MainWindow *mainWindow = new MainWindow;
  QsLogging::DestinationPtr objectDestination(
      QsLogging::DestinationFactory::MakeFunctorDestination(
          mainWindow, SLOT(Log(QString, int))));
  logger.addDestination(objectDestination);

  mainWindow->show();
  /*
  FramelessWindow framelessWindow;
  framelessWindow.setWindowIcon(
      app.style()->standardIcon(QStyle::SP_DesktopIcon));
  framelessWindow.setContent(mainWindow);
  framelessWindow.show();
  */
  return app.exec();
}
