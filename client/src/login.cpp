#include "login.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "client.h"
#include "ui_login.h"
// Конструктор класса основного окна
Login::Login(QWidget *parent) : QMainWindow(parent), ui(new Ui::Login) {
  ui->setupUi(this);  // Инициализация интерфейса
  client = Client::getInstance();
  connect(ui->goToRegisterButton, SIGNAL(clicked()), this,
          SLOT(onGoToRegisterButtonsClicked()));
  connect(ui->logInButton, SIGNAL(clicked()), this,
          SLOT(onLogInbuttonClicked()));
  connect(client, SIGNAL(handleMessage(QString)), this,
          SLOT(loginResponse(QString)));
}

Login::~Login() { delete ui; }  // Деструктор класса основного окна

void Login::onGoToRegisterButtonsClicked() {
  registerWindow = new RegisterWindow(this);
  registerWindow->show();
}

void Login::onLogInbuttonClicked() {
  QString login = ui->loginField->text();
  QString password = ui->passwordField->text();
  client->login(login, password);
}

void Login::loginResponse(QString response) {
  QJsonDocument jsonDocument = QJsonDocument::fromJson(response.toUtf8());
  if (!jsonDocument.isNull() && jsonDocument.isObject()) {
    QJsonObject jsonObject = jsonDocument.object();
    if (jsonObject.contains("id")) {
      int id = jsonObject.value("id").toInt();
      client->setId(id);
      if (jsonObject.contains("role_id")) {
        int role_id = jsonObject.value("role_id").toInt();
        if (role_id == 0) {
          adminTableWindow = new AdminTableWindow(this);
          adminTableWindow->show();
        } else {
          exercicesTableWindow = new ExercicesTableWindow(this);
          exercicesTableWindow->show();
          this->close();
        }
      }
    }
  } else {
    qDebug() << "Login failed. Invalid response.";
  }
}
