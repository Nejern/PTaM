#include "functions.h"
#include "tcpserver.h"
#include <QSignalSpy>
#include <QtTest/QtTest>

class Test : public QObject {
  Q_OBJECT

private slots:
  void testConstructor();
  void testSlotNewConnection();
  void testSlotServerRead();
  void testSlotClientDisconnected();
};

void Test::testConstructor() {
  MyTcpServer server;
  QCOMPARE(server.getServerStatus(), true);
}

void Test::testSlotNewConnection() {
  MyTcpServer server;
  QTcpSocket *socket = new QTcpSocket();
  QSignalSpy spy(socket, SIGNAL(connected()));
  socket->connectToHost(QHostAddress::LocalHost, 33333);
  spy.wait();
  QCOMPARE(spy.count(), 1);
  delete socket;
}

void Test::testSlotServerRead() {
  MyTcpServer server;
  QTcpSocket *socket = new QTcpSocket();
  socket->connectToHost(QHostAddress::LocalHost, 33333);
  QByteArray testMessage = "Hello, World!\r\n";
  socket->write(testMessage);
  socket->waitForBytesWritten();
  socket->waitForReadyRead();
  QByteArray receivedMessage = socket->readAll();
  QCOMPARE(receivedMessage, ServerFunctions::parse(testMessage));
  delete socket;
}

void Test::testSlotClientDisconnected() {
  MyTcpServer server;
  QTcpSocket *socket = new QTcpSocket();
  QSignalSpy spy(&server, SIGNAL(destroyed(QObject *)));
  socket->connectToHost(QHostAddress::LocalHost, 33333);
  socket->disconnectFromHost();
  spy.wait();
  QCOMPARE(spy.count(), 0);
  delete socket;
}

QTEST_MAIN(Test)
#include "test.moc"
