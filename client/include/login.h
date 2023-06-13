#include <QMainWindow>

#include "admintablewindow.h"
#include "client.h"
#include "exercicestablewindow.h"
#include "registerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

/// Класс основного окна
class Login : public QMainWindow {
  Q_OBJECT

public:
  /**
   * @brief Конструктор класса Login.
   * @param parent указатель на родительский виджет.
   */
  Login(QWidget *parent = nullptr); // Конструктор класса
  ~Login();                         // Деструктор класса

private slots:

  /**
   * @brief Обработчик нажатия кнопки "Войти".
   */
  void onLogInbuttonClicked(); // Обработчик нажатия кнопки "Войти"

  /**
   * @brief Обработчик нажатия кнопки "Зарегистрироваться".
   */
  void onGoToRegisterButtonsClicked(); /// Обработчик нажатия кнопки
                                       /// "Зарегистрироваться"
  /**
   * @brief Обработчик ответа сервера на запрос авторизации.
   * @param response ответ сервера.
   */
  void loginResponse(
      QString response); /// Обработчик ответа сервера на запрос авторизации

private:
  RegisterWindow *registerWindow; /// Создание объекта окна регистрации
  ExercicesTableWindow
      *exercicesTableWindow; /// Создание объекта окна таблицы упражнений
  AdminTableWindow
      *adminTableWindow; /// Создание объекта окна таблицы администратора
  Ui::Login *ui;         /// Создание указателя типа Login
  Client *client;        /// Создание указателя типа Client
};
