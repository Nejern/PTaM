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
  void login(QString login, QString password);
  void registerUser(QString login, QString password, QString firstname,
                    QString surname, QString patronymic, QString studygroup);
  void getGrades();
  void checkExercise(int exercise, QString answer, QString exercise_data);
  void setId(int id);
  int getId();
 signals:
  void handleMessage(QString message);

 private slots:
  void slotServerRead();

 private:
  int userId;
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
