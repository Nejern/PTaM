#include "mainwindow.h"
#include "ui_mainwindow.h"

// Конструктор класса основного окна
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this); // Инициализация интерфейса
}

MainWindow::~MainWindow() { delete ui; } // Деструктор класса основного окна
