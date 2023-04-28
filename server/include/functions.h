#pragma once

#include <QJsonDocument>
#include <QJsonObject>

class ServerFunctions {
public:
  static QByteArray parse(const QString &message);

private:
  static QByteArray selectCommand(const QJsonDocument &json);
  static QByteArray registerUser(const QJsonObject &json);
  static QByteArray loginUser(const QJsonObject &json);
};
