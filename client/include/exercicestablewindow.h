#ifndef EXERCICESTABLEWINDOW_H
#define EXERCICESTABLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ExercicesTableWindow;
}

class ExercicesTableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExercicesTableWindow(QWidget *parent = nullptr);
    ~ExercicesTableWindow();

private:
    Ui::ExercicesTableWindow *ui;
};

#endif // EXERCICESTABLEWINDOW_H
