#ifndef EXERCICEWINDOW_H
#define EXERCICEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ExerciceWindow;
}

class ExerciceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExerciceWindow(QWidget *parent = nullptr);
    ~ExerciceWindow();

private:
    Ui::ExerciceWindow *ui;
};

#endif // EXERCICEWINDOW_H
