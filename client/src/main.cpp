#include <QApplication>
#include <QTimer>

#include "client.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);  // Создание объекта приложения
  Client::getInstance();
  Client::getInstance()->sendData("{}\n");
  MainWindow w;  // Создание объекта главного окна
  w.show();
  return a.exec();  // Выход из приложения при закрытии главного окна
}
