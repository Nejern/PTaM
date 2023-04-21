#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Класс основного окна
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr); // Конструктор класса
  ~MainWindow();                         // Деструктор класса

// private slots:

private:
  Ui::MainWindow *ui; // Создание указателя типа MainWindow
};
