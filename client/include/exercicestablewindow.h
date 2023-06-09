#ifndef EXERCICESTABLEWINDOW_H
#define EXERCICESTABLEWINDOW_H

#include <QMainWindow>

#include "exercicewindow.h"

namespace Ui {
class ExercicesTableWindow;
}

class ExercicesTableWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса ExercicesTableWindow.
   * @param parent указатель на родительский виджет.
   */
  explicit ExercicesTableWindow(QWidget *parent = nullptr);
  ~ExercicesTableWindow();
 private slots:

  /**
   * @brief Обработчик нажатия на первую кнопку "Решить".
   */
  void onExerciseButton1clicked();

  /**
   * @brief Обработчик нажатия на вторую кнопку "Решить".
   */
  void onExerciseButton2clicked();

  /**
   * @brief Обработчик нажатия на третью кнопку "Решить".
   */
  void onExerciseButton3clicked();

  /**
   * @brief Обработчик нажатия на четвертую кнопку "Решить".
   */
  void onExerciseButton4clicked();

  /**
   * @brief Обработчик нажатия на пятую кнопку "Решить".
   */
  void onExerciseButton5clicked();

 private:
  ExerciceWindow *exerciceWindow;  // Создание указателя на окно с упражнением
  Ui::ExercicesTableWindow *ui;  // Указатель на форму окна
};

#endif  // EXERCICESTABLEWINDOW_H
