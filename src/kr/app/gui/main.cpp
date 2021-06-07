#include "dark_style.h"
#include "framelesswindow/framelesswindow.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setStyle(new DarkStyle);
  QApplication::setPalette(QApplication::style()->standardPalette());

  FramelessWindow framelessWindow;
  framelessWindow.setWindowIcon(
      a.style()->standardIcon(QStyle::SP_DesktopIcon));

  MainWindow *mainWindow = new MainWindow;
  framelessWindow.setContent(mainWindow);
  framelessWindow.show();
  return a.exec();
}
