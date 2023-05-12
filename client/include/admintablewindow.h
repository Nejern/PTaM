#ifndef ADMINTABLEWINDOW_H
#define ADMINTABLEWINDOW_H

#include <QMainWindow>
#include <QString>

#include "client.h"
namespace Ui {
class AdminTableWindow;
}

class AdminTableWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit AdminTableWindow(QWidget *parent = nullptr);
  ~AdminTableWindow();

 private slots:
  void createTable(QString response);

 private:
  Ui::AdminTableWindow *ui;
  Client *client;
};

#endif  // ADMINTABLEWINDOW_H
