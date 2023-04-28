#pragma once

#include <QJsonDocument>
#include <QJsonObject>

class ServerFunctions {
public:
  static QByteArray parse(QString message);

private:
  static QByteArray selectCommand(QJsonDocument json);
  static QByteArray registerUser(QJsonObject json);
  static QByteArray loginUser(QJsonObject json);
};
