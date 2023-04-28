#include "login.h"

#include "ui_login.h"
// Конструктор класса основного окна
Login::Login(QWidget *parent) : QMainWindow(parent), ui(new Ui::Login) {
  ui->setupUi(this); // Инициализация интерфейса
  connect(ui->goToRegisterButton, SIGNAL(clicked()), this,
          SLOT(onGoToRegisterButtonsClicked()));
  connect(ui->logInButton, SIGNAL(clicked()), this,
          SLOT(onLogInbuttonClicked()));
}

Login::~Login() { delete ui; }  // Деструктор класса основного окна

void Login::onGoToRegisterButtonsClicked() {
 registerWindow = new RegisterWindow(this);
  registerWindow->show();
}

void Login::onLogInbuttonClicked() {
  exercicesTableWindow = new ExercicesTableWindow(this);
  exercicesTableWindow->show();
}