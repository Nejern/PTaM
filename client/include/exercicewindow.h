#ifndef EXERCICEWINDOW_H
#define EXERCICEWINDOW_H

#include "client.h"
#include <QMainWindow>

namespace Ui {
class ExerciceWindow;
}

class ExerciceWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit ExerciceWindow(QWidget *parent = nullptr, int excerciseId = 0);
  ~ExerciceWindow();

  void setExcercise();

private slots:
  void onAnswerButtonClick();
  void exerciseHandeler(QString response);

private:
  Ui::ExerciceWindow *ui;
  int excerciseId;
  Client *client;
  QString excerciseRawData;
};

#endif // EXERCICEWINDOW_H
