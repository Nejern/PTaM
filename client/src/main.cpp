#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Создание объекта приложения
    MainWindow w; // Создание объекта главного окна
    w.show(); // Обтображение главного окна
    return a.exec(); // Выход из приложения при закрытии главного окна
}
