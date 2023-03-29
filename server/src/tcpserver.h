#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QtNetwork>


/**
 * @brief Класс для работы с TCP сервером.
 *
 * Данный класс предоставляет методы для установки соединения с клиентами,
 * чтения и записи данных в сеть.
 */
class MyTcpServer : public QObject {
  Q_OBJECT

public:
  /**
   * @brief Конструктор класса.
   *
   * @param parent - указатель на родительский объект.
   */
  explicit MyTcpServer(QObject *parent = nullptr);

  /**
   * @brief Деструктор класса.
   */
  ~MyTcpServer();

public slots:
  /**
   * @brief Слот для установки соединения с клиентом.
   *
   * Слот, вызываемый при новом соединении клиента с сервером.
   * Метод устанавливает соединение и добавляет указатель на объект QTcpSocket в
   * вектор tcpSockets.
   */
  void slotNewConnection();

  /**
   * @brief Слот для отключения клиента.
   *
   * Слот, вызываемый при отключении клиента от сервера.
   * Метод удаляет указатель на объект QTcpSocket из вектора tcpSockets.
   */
  void slotClientDisconnected();

  /**
   * @brief Слот для чтения данных от сервера.
   *
   * Слот, вызываемый при появлении новых данных от клиента.
   * Метод читает данные и обрабатывает их.
   */
  void slotServerRead();

private:
  QTcpServer *tcpServer; ///< Указатель на объект QTcpServer.
  QVector<QTcpSocket *> tcpSockets; ///< Вектор указателей на объекты QTcpSocket
                                    ///< для хранения подключенных клиентов.
  int server_status; ///< Статус сервера.
};
#endif
