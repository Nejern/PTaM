#include <db.h>
#include <functions.h>

QByteArray ServerFunctions::selectCommand(const QJsonDocument &json) {
  const QJsonObject obj = json.object();
  if (!obj.contains("command") || !obj["command"].isString()) {
    return "Invalid command\n";
  }
  const QString command = obj["command"].toString();
  if (command == "register") {
    return registerUser(obj);
  } else if (command == "login") {
    return loginUser(obj);
  } else {
    return "Invalid command\n";
  }
}

QByteArray ServerFunctions::parse(const QString &message) {
  const QJsonDocument json = QJsonDocument::fromJson(message.toUtf8());
  if (json.isNull() || !json.isObject()) {
    return "Invalid JSON\n";
  }
  return selectCommand(json);
}

QByteArray ServerFunctions::registerUser(const QJsonObject &json) {
  const QString login = json.value("login").toString();
  const QString password = json.value("password").toString();

  if (login.isEmpty() || password.isEmpty()) {
    return "Missing 'login' or 'password' field in JSON\n";
  }

  const QMap<QString, QVariant> userdata{
      {"login", login},
      {"password", password},
      {"role_id", 1},
  };
  const QMap<QString, QMap<QString, QVariant>> data{
      {"user", userdata},
  };

  if (DB::makeInsertQuery(data)) {
    return "Registration success\n";
  } else {
    return "Registration failed\n";
  }
}

QByteArray ServerFunctions::loginUser(const QJsonObject &json) {
  const QString login = json.value("login").toString();
  const QString password = json.value("password").toString();

  if (login.isEmpty() || password.isEmpty()) {
    return "Missing 'login' or 'password' field in JSON\n";
  }

  const QString query =
      QString("SELECT * FROM user WHERE login = '%1' AND password = '%2'")
          .arg(login, password);
  const QMap<QString, QVariant> result = DB::getData(query);
  if (result.isEmpty()) {
    return "Login failed\n";
  } else {
    const QJsonDocument resultJson = QJsonDocument::fromVariant(result);
    return resultJson.toJson(QJsonDocument::Compact) + "\n";
  }
}
