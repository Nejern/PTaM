#include "tcpserver.h"

#include <QCoreApplication>
#include <QDebug>

MyTcpServer::~MyTcpServer() {
  // mTcpSocket->close();
  tcpServer->close();
  server_status = 0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {
  tcpServer = new QTcpServer(this);
  connect(tcpServer, &QTcpServer::newConnection, this,
          &MyTcpServer::slotNewConnection);

  if (!tcpServer->listen(QHostAddress::Any, 33333)) {
    qDebug() << "server is not started";
  } else {
    server_status = 1;
    qDebug() << "server is started";
  }
}

void MyTcpServer::slotNewConnection() {
  if (server_status == 1) {
    QTcpSocket *currTcpSocket;
    currTcpSocket = tcpServer->nextPendingConnection();
    currTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(currTcpSocket, &QTcpSocket::readyRead, this,
            &MyTcpServer::slotServerRead);
    connect(currTcpSocket, &QTcpSocket::disconnected, this,
            &MyTcpServer::slotClientDisconnected);
    tcpSockets.push_back(currTcpSocket);
  }
}

void MyTcpServer::slotServerRead() {
  QTcpSocket *currTcpSocket;
  currTcpSocket = (QTcpSocket*)sender();
  while (currTcpSocket->bytesAvailable() > 0) {
    QByteArray array = currTcpSocket->readAll();
    currTcpSocket->write(array);
  }
}

void MyTcpServer::slotClientDisconnected() {
  QTcpSocket *currTcpSocket = (QTcpSocket*)sender();
  currTcpSocket->close();
}
