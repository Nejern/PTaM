#include "client.h"
#include "login.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv); // Создание объекта приложения
  Client::getInstance();
  Login w; // Создание объекта главного окна
  w.show();
  return a.exec(); // Выход из приложения при закрытии главного окна
}
