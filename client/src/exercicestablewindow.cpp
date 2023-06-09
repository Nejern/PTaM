#include "exercicestablewindow.h"
#include "ui_exercicestablewindow.h"

ExercicesTableWindow::ExercicesTableWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ExercicesTableWindow) {
  ui->setupUi(this);
  connect(ui->makeExcerciseButton1, SIGNAL(clicked()), this,
          SLOT(onExerciseButton1clicked()));
  connect(ui->makeExcerciseButton2, SIGNAL(clicked()), this,
          SLOT(onExerciseButton2clicked()));
  connect(ui->makeExcerciseButton3, SIGNAL(clicked()), this,
          SLOT(onExerciseButton3clicked()));
  connect(ui->makeExcerciseButton4, SIGNAL(clicked()), this,
          SLOT(onExerciseButton4clicked()));
  connect(ui->makeExcerciseButton5, SIGNAL(clicked()), this,
          SLOT(onExerciseButton5clicked()));
}

ExercicesTableWindow::~ExercicesTableWindow() { delete ui; }

void ExercicesTableWindow::onExerciseButton1clicked() {
  exerciceWindow = new ExerciceWindow(this->window(), 1);
  exerciceWindow->show();
}

void ExercicesTableWindow::onExerciseButton2clicked() {
  exerciceWindow = new ExerciceWindow(this->window(), 2);
  exerciceWindow->show();
}

void ExercicesTableWindow::onExerciseButton3clicked() {
  exerciceWindow = new ExerciceWindow(this->window(), 3);
  exerciceWindow->show();
}

void ExercicesTableWindow::onExerciseButton4clicked() {
  exerciceWindow = new ExerciceWindow(this->window(), 4);
  exerciceWindow->show();
}

void ExercicesTableWindow::onExerciseButton5clicked() {
  exerciceWindow = new ExerciceWindow(this->window(), 5);
  exerciceWindow->show();
}
