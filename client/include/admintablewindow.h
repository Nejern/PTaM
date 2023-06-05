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
  void on_filtersBox_currentIndexChanged(int index);
  void on_directionBox_currentIndexChanged(int index);
  void createTable(QString response);

 private:
  void init();
  Ui::AdminTableWindow *ui;
  Client *client;
  bool filterDirection = false;
  int filterIndex = 0;
  bool initialized = false;

  const QMap<int, QString> filters = {{0, "default"},
                                      {1, "surname"},
                                      {2, "studygroup"},
                                      {3, "exercise"},
                                      {4, "grades"}};
};

#endif  // ADMINTABLEWINDOW_H
