#ifndef MyDB_H
#define MyDB_H

#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "singleton.h"

// Класс для работы с базой данных SQLite
class MyDB : public Singleton {
 private:
  MyDB() = delete;
  MyDB(const MyDB &Db) = delete;
  static void openDB() {
    qDebug() << "MyDB()\n";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Test");
    if (!db.open()) qDebug() << db.lastError().text();
  }

 public:
  static QSqlDatabase db;

  static QString query_select() {
    static QSqlQuery query = QSqlQuery(db);
    query.exec("SELECT * FROM User");
    if (query.next()) {
      QSqlRecord rec = query.record();
      const int loginIndex = rec.indexOf("login");  // номер "столбца"
      const int passwordIndex = rec.indexOf("password");
      return query.value(loginIndex).toString() + " " +
             query.value(passwordIndex).toString();
    } else
      return "Sorry, something went wrong";
  }

  static void createDB() {
    Singleton::getInstance();
    if (!db.isOpen()) {
      openDB();
    }
  }

  static void close() {
    if (db.isOpen()) {
      db.close();
    }
  }
};

QSqlDatabase MyDB::db = QSqlDatabase();

#endif  // MyDB_H
