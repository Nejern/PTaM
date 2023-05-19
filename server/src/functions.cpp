#include <db.h>
#include <excercises.h>
#include <functions.h>

#include <QJsonArray>

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
  } else if (command == "checkExercise") {
    return checkExercise(obj);
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
  QSqlQuery result = DB::getQsqlData(query);

  QJsonArray jsonArray;
  while (result.next()) {
    QJsonObject jsonObject;
    jsonObject["firstname"] = result.value("firstname").toString();
    jsonObject["surname"] = result.value("surname").toString();
    jsonObject["patronymic"] = result.value("patronymic").toString();
    jsonObject["studygroup"] = result.value("studygroup").toString();
    jsonObject["excercise"] = result.value("excercise").toString();
    jsonObject["grade"] = result.value("grade").toString();
    jsonArray.append(jsonObject);
  }

  if (jsonArray.isEmpty()) {
    return "No grades\n";
  } else {
    QJsonDocument resultJson(jsonArray);
    return resultJson.toJson(QJsonDocument::Compact);
  }
}

QByteArray ServerFunctions::checkExercise(const QJsonObject &json) {
  if (!json.contains("student_id") || !json.contains("exercise") ||
      !json.contains("answer")) {
    return "Missing field in JSON\n";
  }
  const QString student_id = json.value("student_id").toString();
  const int excercise = json.value("exercise").toInt();
  const QString answer = json.value("answer").toString();
  bool result = false;
  switch (excercise) {
    case 1:
      result = Excercises::task1(answer);
      break;
    case 2:
      result = Excercises::task2(answer);
      break;
    case 3:
      result = Excercises::task3(answer);
      break;
    case 4:

      result = Excercises::task4(answer);
      break;
    case 5:
      result = Excercises::task5(answer);
      break;
  }

  const QMap<QString, QVariant> userdata{
      {"student_id", student_id},
      {"exercise", excercise},
      {"grade", static_cast<int>(result)},
  };
  const QMap<QString, QMap<QString, QVariant>> inUserData{{"grade", userdata}};
  DB::makeInsertQuery(inUserData);
  if (result) {
    return "Correct answer\n";
  } else {
    return "Incorrect answer\n";
  }
}