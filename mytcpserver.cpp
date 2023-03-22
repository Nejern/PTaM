#include "mytcpserver.h"

#include <QCoreApplication>
#include <QDebug>

MyTcpServer::~MyTcpServer() {
  // mTcpSocket->close();
  mTcpServer->close();
  server_status = 0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {
  mTcpServer = new QTcpServer(this);
  connect(mTcpServer, &QTcpServer::newConnection, this,
          &MyTcpServer::slotNewConnection);

  if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
    qDebug() << "server is not started";
  } else {
    server_status = 1;
    qDebug() << "server is started";
  }
}

void MyTcpServer::slotNewConnection() {
  if (server_status == 1) {
    QTcpSocket *current_mTcpSocket;
    current_mTcpSocket = mTcpServer->nextPendingConnection();
    mTcpSocket[current_mTcpSocket->socketDescriptor()] = current_mTcpSocket;
    current_mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(current_mTcpSocket, &QTcpSocket::readyRead, this,
            &MyTcpServer::slotServerRead);
    connect(current_mTcpSocket, &QTcpSocket::disconnected, this,
            &MyTcpServer::slotClientDisconnected);
  }
}

void MyTcpServer::slotServerRead() {
  QTcpSocket *current_mTcpSocket;
  current_mTcpSocket = mTcpSocket[mTcpServer->socketDescriptor()];
  while (current_mTcpSocket->bytesAvailable() > 0) {
    QByteArray array = current_mTcpSocket->readAll();
    current_mTcpSocket->write(array);
  }
}

void MyTcpServer::slotClientDisconnected() {
  QTcpSocket *current_mTcpSocket = mTcpSocket[mTcpServer->socketDescriptor()];
  current_mTcpSocket->close();
}
