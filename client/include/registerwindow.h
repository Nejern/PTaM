#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include <QMainWindow>

#include "client.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit RegisterWindow(QWidget *parent = nullptr);
  ~RegisterWindow();

 private slots:
  void onRegisterButtonClicked();
  void registerResponse(QString response);

 private:
  Ui::RegisterWindow *ui;
  Client *client;  // Создание указателя типа Client
};

#endif  // REGISTERWINDOW_H
