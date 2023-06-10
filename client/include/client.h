#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QScopedPointer>
#include <QTcpSocket>

class SingletonDestroyer;

class Client : public QObject {
  Q_OBJECT
 public:
  /**
   * @brief Возвращает экземпляр класса Client (singleton).
   * @return Экземпляр класса Client.
   */
  static Client *getInstance();

  /**
   * @brief Отправляет запрос на сервер.
   * @param query запрос.
   */
  void sendData(QString query);
  ~Client();

  /**
   * @brief Отправляет запрос на сервер для авторизации.
   * @param login логин пользователя.
   * @param password пароль пользователя.
   */
  void login(QString login, QString password);

  /**
   * @brief Отправляет запрос на сервер для регистрации.
   * @param login логин пользователя.
   * @param password пароль пользователя.
   * @param firstname имя пользователя.
   * @param surname фамилия пользователя.
   * @param patronymic отчество пользователя.
   * @param studygroup учебная группа пользователя.
   */
  void registerUser(QString login, QString password, QString firstname,
                    QString surname, QString patronymic, QString studygroup);

  /**
   * @brief Отправляет запрос на сервер для получения оценок пользователей.
   * @param filter тип сортировки.
   * @param direction направление сортировки.
   */
  void getGrades(QString filter, bool direction);

  /**
   * @brief Отправляет запрос на сервер для проверки ответа пользователя на
   упражнение.
   * @param exercise номер упражнения.
   * @param answer ответ пользователя.
   * @param exercise_data данные упражнения.
   */
  void checkExercise(int exercise, QString answer, QString exercise_data);

  /**
   * @brief Устанавливает id пользователя.
   * @param id id пользователя.
   */
  void setId(int id);

  /**
   * @brief Возвращает id пользователя.
   * @return id пользователя.
   */
  int getId();
 signals:

  /**
   * @brief Сигнал, который вызывается при получении ответа от сервера.
   * @param message ответ сервера.
   */
  void handleMessage(QString message);

 private slots:

  /**
   * @brief Слот, который вызывается при получении данных от сервера.
   */
  void slotServerRead();

 private:
  int userId;                                  // id пользователя
  explicit Client(QObject *parent = nullptr);  // Конструктор
  static Client *p_instance;  // Экземпляр класса Client
  static QScopedPointer<SingletonDestroyer>
      destroyer;  // Указатель на класс SingletonDestroyer
  QTcpSocket *mTcpSocket;  // Сокет
};

class SingletonDestroyer {
 public:
  /*
   * @brief Конструктор класса SingletonDestroyer.
   * @param p указатель на экземпляр класса Client.
   */
  void initialize(Client *p) { p_instance = p; }
  ~SingletonDestroyer() { delete p_instance; }

 private:
  Client *p_instance;  // Указатель на экземпляр класса Client
};

#endif  // CLIENT_H
