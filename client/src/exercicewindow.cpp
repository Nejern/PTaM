#include "exercicewindow.h"

#include "ui_exercicewindow.h"

ExerciceWindow::ExerciceWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ExerciceWindow) {
  ui->setupUi(this);
}

ExerciceWindow::~ExerciceWindow() { delete ui; }
