#include "exercicestablewindow.h"
#include "ui_exercicestablewindow.h"

ExercicesTableWindow::ExercicesTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExercicesTableWindow)
{
    ui->setupUi(this);
}

ExercicesTableWindow::~ExercicesTableWindow()
{
    delete ui;
}
