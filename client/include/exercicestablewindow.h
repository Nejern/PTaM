#ifndef EXERCICESTABLEWINDOW_H
#define EXERCICESTABLEWINDOW_H

#include "exercicewindow.h"
#include <QMainWindow>

namespace Ui {
class ExercicesTableWindow;
}

class ExercicesTableWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit ExercicesTableWindow(QWidget *parent = nullptr);
  ~ExercicesTableWindow();
private slots:
  void onExerciseButton1clicked();
  void onExerciseButton2clicked();
  void onExerciseButton3clicked();
  void onExerciseButton4clicked();
  void onExerciseButton5clicked();

private:
  ExerciceWindow *exerciceWindow; // Создание указателя на окно с упражнением
  Ui::ExercicesTableWindow *ui;
};

#endif // EXERCICESTABLEWINDOW_H
