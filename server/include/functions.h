#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QByteArray>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include <QString>
#include <QStringList>

class ServerFunctions {
 public:
  static QByteArray parse(QString message);

 private:
  static QByteArray selectCommand(QJsonDocument json);
  static QByteArray registerUser(QJsonObject json);
  static QByteArray loginUser(QJsonObject json);
};
#endif
