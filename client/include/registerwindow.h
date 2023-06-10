#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>

#include "client.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса RegisterWindow.
   * @param parent указатель на родительский виджет.
   */
  explicit RegisterWindow(QWidget *parent = nullptr);
  ~RegisterWindow();

 private slots:
  /**
   * @brief Обработчик нажатия на кнопку "Зарегистрироваться".
   */
  void onRegisterButtonClicked();

  /**
   * @brief Обработчик ответа сервера на запрос регистрации.
   * @param response ответ сервера.
   */
  void registerResponse(QString response);

 private:
  Ui::RegisterWindow *ui;  // Указатель на форму окна
  Client *client;  // Создание указателя типа Client
};

#endif  // REGISTERWINDOW_H
