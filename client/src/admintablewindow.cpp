#include "admintablewindow.h"
#include "ui_admintablewindow.h"

AdminTableWindow::AdminTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminTableWindow)
{
    ui->setupUi(this);
}

AdminTableWindow::~AdminTableWindow()
{
    delete ui;
}
