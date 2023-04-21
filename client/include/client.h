#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QScopedPointer>
#include <QTcpSocket>

class SingletonDestroyer;

class Client : public QObject {
  Q_OBJECT
 public:
  static Client* getInstance();
  void sendData(QString query);
  ~Client();
 signals:
  void handleMessage(QString message);

 private slots:
  void slotServerRead();

 private:
  explicit Client(QObject* parent = nullptr);
  static Client* p_instance;
  static QScopedPointer<SingletonDestroyer> destroyer;
  QTcpSocket* mTcpSocket;
};

class SingletonDestroyer {
 public:
  void initialize(Client* p) { p_instance = p; }
  ~SingletonDestroyer() { delete p_instance; }

 private:
  Client* p_instance;
};

#endif  // CLIENT_H
