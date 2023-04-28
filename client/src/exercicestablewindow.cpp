#include "exercicestablewindow.h"

#include "ui_exercicestablewindow.h"

ExercicesTableWindow::ExercicesTableWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ExercicesTableWindow) {
  ui->setupUi(this);
  connect(ui->makeExcerciseButton2, SIGNAL(clicked()), this,
          SLOT(onSolveButtonClick()));
}

ExercicesTableWindow::~ExercicesTableWindow() { delete ui; }

void ExercicesTableWindow::onSolveButtonClick() {
  exerciceWindow = new ExerciceWindow(this);
  exerciceWindow->show();
}