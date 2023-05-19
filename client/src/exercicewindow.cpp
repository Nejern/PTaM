#include "exercicewindow.h"

#include "ui_exercicewindow.h"

ExerciceWindow::ExerciceWindow(QWidget *parent, int excerciseNumber)
    : QMainWindow(parent), ui(new Ui::ExerciceWindow) {
  ui->setupUi(this);
  connect(ui->answerButton, SIGNAL(clicked()), this,
          SLOT(onAnswerButtonClick()));
  excerciseId = excerciseNumber;
  client = Client::getInstance();
  setExcercise();
}

ExerciceWindow::~ExerciceWindow() { delete ui; }

void ExerciceWindow::setExcercise() {
  switch (excerciseId) {
    case 1:
      ui->excerciseText->setText("1");
      break;

    case 2:
      ui->excerciseText->setText("2");
      break;
    case 3:
      ui->excerciseText->setText("3");
      break;
    case 4:
      ui->excerciseText->setText("4");
      break;
    case 5:
      ui->excerciseText->setText("5");
      break;
  }
}

void ExerciceWindow::onAnswerButtonClick() {
  QString answer = ui->answerLineEdit->text();
  client->checkExercise(excerciseId, answer);
}