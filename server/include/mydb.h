#pragma once

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>

#include "singleton.h"

// Класс для работы с базой данных SQLite
class MyDB : public Singleton {
 private:
  MyDB() = delete;
  MyDB(const MyDB& Db) = delete;

  static void openDB() {
    if (db.isOpen()) {
      return;
    }
    qDebug() << "MyDB()\n";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Test.sql");
    if (!db.open()) qDebug() << db.lastError().text();
  }

 public:
  // Статическая переменная для хранения базы данных
  static QSqlDatabase db;
  // Функция для создания базы данных
  static void createDB() {
    Singleton::getInstance();
    openDB();
    createTables();
  }
  // Функция для закрытия базы данных
  static void close() {
    if (db.isOpen()) {
      db.close();
    }
  }
  // Функция для выполнения запроса на вставку данных в таблицу
  static bool insertData(const QString& queryString) {
    openDB();
    QSqlQuery query(db);
    query.exec("PRAGMA foreign_keys = ON");
    // Выполнение запроса
    if (!query.exec(queryString)) {
      qDebug() << "Failed to execute query:" << query.lastError().text();
      return false;
    }
    return true;
  }

  // Функция для выполнения запроса и получения результатов в виде QMap
  static QMap<QString, QVariant> getData(const QString& request) {
    QMap<QString, QVariant> resultMap;

    // Открытие базы данных
    if (!db.isOpen()) {
      openDB();
    }

    // Выполнение запроса
    QSqlQuery query(db);
    if (!query.exec(request)) {
      qDebug() << "Error executing query:" << query.lastError().text();
      return resultMap;
    }
    // Обработка результатов
    while (query.next()) {
      QSqlRecord record = query.record();
      for (int i = 0; i < record.count(); i++) {
        resultMap[record.fieldName(i)] = query.value(i);
      }
    }

    // Закрытие базы данных
    db.close();

    return resultMap;
  }
  // Функция для составления запроса на вставку данных в таблицу
  static bool makeInsertQuery(
      const QMap<QString, QMap<QString, QVariant>>& data) {
    QString table = data.firstKey();
    QMap<QString, QVariant> columnData = data.value(table);

    QString query = QString("INSERT INTO %1 (").arg(table);

    QStringList columns;
    QList<QString> values;

    for (auto it = columnData.constBegin(); it != columnData.constEnd(); ++it) {
      if (it.key() != "command") {
        columns.append(it.key());
        values.append(it.value().toString());
      }
    }

    query += columns.join(", ");
    query += QString(") VALUES ('%1')").arg(values.join("', '"));

    if (insertData(query)) {
      qDebug() << "OK";
      return true;
    } else {
      qDebug() << "Error";
      return false;
    }
  }

  // Функция для создания таблиц
  static void createTables() {
    QSqlQuery query(db);
    query.exec("PRAGMA foreign_keys = ON");
    MyDB::insertData(
        "CREATE TABLE IF NOT EXISTS roles ("
        "role_id INT PRIMARY KEY,"
        "role TEXT"
        ");");
    MyDB::insertData(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "login TEXT,"
        "password TEXT,"
        "role_id INT"
        ");");

    MyDB::insertData(
        "CREATE TABLE IF NOT EXISTS grades ("
        "student_id INT,"
        "excercise INT,"
        "grade INT"
        ");");
    MyDB::insertData(
        "CREATE TABLE IF NOT EXISTS students ("
        "id INT,"
        "firstname TEXT,"
        "surname TEXT,"
        "patronymic TEXT,"
        "studygroup TEXT"
        ");");
  }
  // Функция для удаления таблиц
  static void dropTables() {
    MyDB::insertData("DROP TABLE IF EXISTS users;");
    MyDB::insertData("DROP TABLE IF EXISTS roles;");
    MyDB::insertData("DROP TABLE IF EXISTS students;");
    MyDB::insertData("DROP TABLE IF EXISTS grades;");
  }
};
