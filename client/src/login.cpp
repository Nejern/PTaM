#include "login.h"
#include "ui_login.h"

// Конструктор класса основного окна
Login::Login(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Login) {
  ui->setupUi(this); // Инициализация интерфейса
}

Login::~Login() { delete ui; } // Деструктор класса основного окна
