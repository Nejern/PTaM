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
  } else if (command == "getGrades") {
    return getGrades();
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
  const QMap<QString, QMap<QString, QVariant>> inUserData{
      {"user", userdata},
  };

  if (DB::makeInsertQuery(inUserData)) {
  } else {
    return "Registration failed\n";
  }

  const QMap<QString, QVariant> studentdata{
      {"user_id", DB::getLastInsertId()},
      {"firstname", json.value("firstname").toString()},
      {"surname", json.value("surname").toString()},
      {"patronymic", json.value("patronymic").toString()},
      {"studygroup", json.value("studygroup").toString()},
  };

  const QMap<QString, QMap<QString, QVariant>> inStudentData{
      {"student", studentdata},
  };

  if (DB::makeInsertQuery(inStudentData)) {
    return "Registration successful\n";
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

QByteArray ServerFunctions::getGrades() {
  const QString query = QString(
      "SELECT student.firstname, student.surname, student.patronymic, "
      "student.studygroup, grade.excercise, grade.grade FROM student JOIN "
      "grade ON student.user_id = grade.student_id;");
  const QMap<QString, QVariant> result = DB::getData(query);
  if (result.isEmpty()) {
    return "No grades\n";
  } else {
    const QJsonDocument resultJson = QJsonDocument::fromVariant(result);
    return resultJson.toJson(QJsonDocument::Compact) + "\n";
  }
}