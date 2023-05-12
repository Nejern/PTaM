#include "registerwindow.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "ui_registerwindow.h"
RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RegisterWindow) {
  ui->setupUi(this);
  client = Client::getInstance();
  connect(ui->registerButton, SIGNAL(clicked()), this,
          SLOT(onRegisterButtonClicked()));
  connect(client, SIGNAL(handleMessage(QString)), this,
          SLOT(registerResponse(QString)));
}

RegisterWindow::~RegisterWindow() { delete ui; }

void RegisterWindow::onRegisterButtonClicked() {
  QString login = ui->loginField->text();
  QString password = ui->passwordField->text();
  QString firstname = ui->firstnameField->text();
  QString surname = ui->surnameField->text();
  QString patronymic = ui->patronymicField->text();
  QString studygroup = ui->studygroupField->text();
  client->registerUser(login, password, firstname, surname, patronymic,
                       studygroup);
}

void RegisterWindow::registerResponse(QString response) {
  QJsonDocument jsonDocument = QJsonDocument::fromJson(response.toUtf8());
  qDebug() << response;
  this->close();
}