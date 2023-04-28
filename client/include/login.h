#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

// Класс основного окна
class Login : public QMainWindow {
  Q_OBJECT

public:
  Login(QWidget *parent = nullptr); // Конструктор класса
  ~Login();                         // Деструктор класса

// private slots:

private:
  Ui::Login *ui; // Создание указателя типа Login
};
