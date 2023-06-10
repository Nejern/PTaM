#ifndef ADMINTABLEWINDOW_H
#define ADMINTABLEWINDOW_H

#include <QMainWindow>
#include <QString>

#include "client.h"

namespace Ui {
class AdminTableWindow;
}

class AdminTableWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса AdminTableWindow.
   * @param parent указатель на родительский виджет.
   */
  explicit AdminTableWindow(QWidget *parent = nullptr);
  ~AdminTableWindow();

 private slots:
  /**
   * @brief Слот, вызываемый при изменении фильтра.
   * @param index индекс выбранного элемента.
   */
  void on_filtersBox_currentIndexChanged(int index);

  /**
   * @brief Слот, вызываемый при изменении направления сортировки.
   * @param index индекс выбранного элемента.
   */
  void on_directionBox_currentIndexChanged(int index);

  /**
   * @brief Слот, вызываемый при получении ответа от сервера.
   * @param response ответ от сервера.
   */
  void createTable(QString response);

 private:
  /**
   * @brief Инициализация окна.
   */
  void init();

  Ui::AdminTableWindow *ui;  // Указатель на объект интерфейса
  Client *client;  // Указатель на объект клиента
  bool filterDirection = false;  // Направление сортировки
  int filterIndex = 0;       // Индекс выбранного фильтра
  bool initialized = false;  // Флаг инициализации окна

  const QMap<int, QString> filters = {{0, "default"},  // Список фильтров
                                      {1, "surname"},
                                      {2, "studygroup"},
                                      {3, "exercise"},
                                      {4, "grades"}};
};

#endif  // ADMINTABLEWINDOW_H
