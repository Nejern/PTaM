#pragma once

#include <QJsonObject>
#include <QJsonDocument>

class ServerFunctions {
 public:
  static QByteArray parse(QString message);

 private:
  static QByteArray selectCommand(QJsonDocument json);
  static QByteArray registerUser(QJsonObject json);
  static QByteArray loginUser(QJsonObject json);
};
