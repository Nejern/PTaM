
#include "client.h"

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
  QString query = "{\"command\":\"login\",\"login\":\"" + login +
                  "\",\"password\":\"" + password + "\"}\n";
  sendData(query);
}

void Client::registerUser(QString login, QString password) {
  QString query = "{\"command\":\"register\",\"login\":\"" + login +
                  "\",\"password\":\"" + password + "\"}\n";
  sendData(query);
}
