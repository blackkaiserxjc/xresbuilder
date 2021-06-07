
#include <kr/core/compiler.h>

#include <QApplication>

#include "dark_style.h"
#include "framelesswindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{

  QApplication app(argc, argv);
  app.setApplicationName("XResBuilder");
  QApplication::setStyle(new DarkStyle);
  QApplication::setPalette(QApplication::style()->standardPalette());

  FramelessWindow framelessWindow;
  framelessWindow.setWindowIcon(
      app.style()->standardIcon(QStyle::SP_DesktopIcon));

  MainWindow *mainWindow = new MainWindow;
  framelessWindow.setContent(mainWindow);
  framelessWindow.show();
  return app.exec();
}
