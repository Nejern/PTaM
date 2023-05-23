
#include "client.h"

#include <QJsonDocument>
#include <QJsonObject>
Client* Client::p_instance = nullptr;
QScopedPointer<SingletonDestroyer> Client::destroyer;

Client::Client(QObject* parent) : QObject(parent) {
  mTcpSocket = new QTcpSocket(this);
  mTcpSocket->connectToHost("127.0.0.1", 33333);
  connect(mTcpSocket, &QTcpSocket::readyRead, this, &Client::slotServerRead);
}

Client* Client::getInstance() {
  if (!p_instance) {
    p_instance = new Client();
    destroyer.reset(new SingletonDestroyer());
    destroyer->initialize(p_instance);
  }
  return p_instance;
}

void Client::sendData(QString query) { mTcpSocket->write(query.toUtf8()); }

void Client::slotServerRead() {
  qDebug() << "Connected";
  QString data = mTcpSocket->readAll();

  qDebug() << data;
  emit handleMessage(data);
}

Client::~Client() {
  mTcpSocket->close();
  delete mTcpSocket;
}

void Client::setId(int id) { userId = id; }

int Client::getId() { return userId; }

void Client::login(QString login, QString password) {
  QJsonObject json;
  json["command"] = "login";
  json["login"] = login;
  json["password"] = password;

  QJsonDocument jsonDocument(json);
  QString query =
      QString::fromUtf8(jsonDocument.toJson(QJsonDocument::Compact)) + "\n";
  sendData(query);
}

void Client::registerUser(QString login, QString password, QString firstname,
                          QString surname, QString patronymic,
                          QString studygroup) {
  QJsonObject json;
  json["command"] = "register";
  json["login"] = login;
  json["password"] = password;
  json["firstname"] = firstname;
  json["surname"] = surname;
  json["patronymic"] = patronymic;
  json["studygroup"] = studygroup;

  QJsonDocument jsonDocument(json);
  QString query =
      QString::fromUtf8(jsonDocument.toJson(QJsonDocument::Compact)) + "\n";
  sendData(query);
}

void Client::getGrades(QString filter) {
  QJsonObject json;
  json["command"] = "getGrades";
  json["filter"] = filter; 
  QJsonDocument jsonDocument(json);
  QString query =
      QString::fromUtf8(jsonDocument.toJson(QJsonDocument::Compact)) + "\n";
  sendData(query);
}

void Client::checkExercise(int exercise, QString answer, QString exercise_data) {
  QJsonObject json;
  json["command"] = "checkExercise";
  json["exercise"] = exercise;
  json["exercise_data"] = exercise_data;
  json["answer"] = answer;
  json["student_id"] = this->userId;
  QJsonDocument jsonDocument(json);
  QString query =
      QString::fromUtf8(jsonDocument.toJson(QJsonDocument::Compact)) + "\n";
  sendData(query);
}