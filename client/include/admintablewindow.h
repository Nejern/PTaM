#ifndef ADMINTABLEWINDOW_H
#define ADMINTABLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminTableWindow;
}

class AdminTableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminTableWindow(QWidget *parent = nullptr);
    ~AdminTableWindow();

private:
    Ui::AdminTableWindow *ui;
};

#endif // ADMINTABLEWINDOW_H
