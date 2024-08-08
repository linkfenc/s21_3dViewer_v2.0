#include <QApplication>

#include "../../controller/controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Controller controller_;
  MainWindow w(&controller_);
  w.show();
  return a.exec();
}
