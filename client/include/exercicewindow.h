#ifndef EXERCICEWINDOW_H
#define EXERCICEWINDOW_H

#include <QMainWindow>

#include "client.h"

namespace Ui {
class ExerciceWindow;
}

class ExerciceWindow : public QMainWindow {
  Q_OBJECT

 public:
  /*
   * @brief Конструктор класса ExerciceWindow.
   * @param parent указатель на родительский виджет.
   * @param excerciseId номер упражнения.
   */
  explicit ExerciceWindow(QWidget *parent = nullptr, int excerciseId = 0);
  ~ExerciceWindow();
  /*
   * @brief Устанавливает упражнение.
   */
  void setExcercise();

 private slots:
  /*
   * @brief Обработчик нажатия на кнопку "Ответить".
   */
  void onAnswerButtonClick();

  /**
   * @brief Обработчик ответа сервера.
   * @param response ответ сервера.
   */
  void exerciseHandeler(QString response);

 private:
  Ui::ExerciceWindow *ui;    // Указатель на форму окна
  int excerciseId;           // Номер упражнения
  Client *client;            // Указатель на клиент
  QString excerciseRawData;  // Данные упражнения
};

#endif  // EXERCICEWINDOW_H
