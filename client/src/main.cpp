#include <QApplication>
#include <QTimer>

#include "client.h"
#include "login.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);  // Создание объекта приложения
  Client::getInstance();
  Client::getInstance()->sendData("{}\n");
  Login w;  // Создание объекта главного окна
  w.show();
  return a.exec();  // Выход из приложения при закрытии главного окна
}
