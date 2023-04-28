#include <QMainWindow>

#include "admintablewindow.h"
#include "exercicestablewindow.h"
#include "registerwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

// Класс основного окна
class Login : public QMainWindow {
  Q_OBJECT

 public:
  Login(QWidget* parent = nullptr);  // Конструктор класса
  ~Login();                          // Деструктор класса

 private slots:
  void onLogInbuttonClicked();  // Обработчик нажатия кнопки "Войти"

  void onGoToRegisterButtonsClicked();  // Обработчик нажатия кнопки
                                        // "Зарегистрироваться"

 private:
  RegisterWindow* registerWindow;  // Создание объекта окна регистрации
  ExercicesTableWindow*
      exercicesTableWindow;  // Создание объекта окна таблицы упражнений
  AdminTableWindow*
      adminTableWindow;  // Создание объекта окна таблицы администратора
  Ui::Login* ui;         // Создание указателя типа Login
};
