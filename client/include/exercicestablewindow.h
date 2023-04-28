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
  explicit ExercicesTableWindow(QWidget *parent = nullptr);
  ~ExercicesTableWindow();
 private slots:
  void onSolveButtonClick();

 private:
  ExerciceWindow *exerciceWindow;  // Создание указателя на окно с упражнением
  Ui::ExercicesTableWindow *ui;
};

#endif  // EXERCICESTABLEWINDOW_H
