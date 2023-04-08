#include "functions.h"

#include "mydb.h"
QByteArray ServerFunctions::parse(QString message) {
  QJsonDocument json = QJsonDocument::fromJson(message.toUtf8());
  if (json.isNull() || !json.isObject()) {
    return "Invalid JSON\n";
  } else {
    return ServerFunctions::selectCommand(json);
  }
  return "Invalid JSON\n";
}

QByteArray ServerFunctions::selectCommand(QJsonDocument json) {
  QJsonObject obj = json.object();
  if (obj.contains("command") && obj["command"].isString()) {
    QString command = obj["command"].toString();
    if (command == "register") {
      return ServerFunctions::registerUser(obj);
    } else if (command == "login") {
      return ServerFunctions::loginUser(obj);
    } else {
      return "Invalid command\n";
    }
  } else {
    return "Invalid command\n";
  }
}

QByteArray ServerFunctions::registerUser(QJsonObject json) {
  if (json.contains("login") && json["login"].isString() &&
      json.contains("password") && json["password"].isString() &&
      json.contains("role_id")) {
    QMap<QString, QVariant> userdata = json.toVariantMap();
    QMap<QString, QMap<QString, QVariant>> data;
    data.insert("users", userdata);

    if (MyDB::makeInsertQuery(data)) {
      return "Registration success\n";
    } else {
      return "Registration failed\n";
    }
  } else {
    return "Invalid JSON\n";
  }
}

QByteArray ServerFunctions::loginUser(QJsonObject json) {
  if (json.contains("login") && json["login"].isString() &&
      json.contains("password") && json["password"].isString()) {
    QMap<QString, QVariant> userdata = json.toVariantMap();
    QMap<QString, QMap<QString, QVariant>> data;
    data.insert("users", userdata);
    QString query = "SELECT * FROM users WHERE login = '" +
                    userdata["login"].toString() + "' AND password = '" +
                    userdata["password"].toString() + "'";
    QMap<QString, QVariant> result = MyDB::getData(query);
    if (result.isEmpty()) {
      return "Login failed\n";
    } else {
      QJsonDocument resultJson = QJsonDocument::fromVariant(result);
      return resultJson.toJson() + "\n";
    }
  }
  return "Login Invalid JSON\n";
}
