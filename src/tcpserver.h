#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QByteArray>
#include <QDebug>
#include <QVector>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>

class MyTcpServer : public QObject {
  Q_OBJECT
 public:
  explicit MyTcpServer(QObject *parent = nullptr);
  ~MyTcpServer();
 public slots:
  void slotNewConnection();
  void slotClientDisconnected();

  void slotServerRead();
  // void slotReadClient();
 private:
  QTcpServer *tcpServer;
  QVector<QTcpSocket*> tcpSockets;
  int server_status;
};
#endif
