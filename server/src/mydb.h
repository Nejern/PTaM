#ifndef MyDB_H
#define MyDB_H

#include <QCoreApplication>
#include <QDebug>
#include <QMap>
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
  static bool buildInsertQuery(
      const QMap<QString, QMap<QString, QString>>& data) {
    QString table = data.firstKey();
    QMap<QString, QString> columnData = data.value(table);

    QString query = QString("INSERT INTO %1 (").arg(table);

    QStringList columns;
    QStringList values;

    for (auto it = columnData.constBegin(); it != columnData.constEnd(); ++it) {
      columns << it.key();
      values << it.value();
    }

    query += columns.join(", ");
    query += QString(") VALUES ('%1')").arg(values.join("', '"));

    if (insertData(query)) {
      qDebug() << "OK";
      return true;
    } else {
      qDebug() << "Error";
    }
  }
};

QSqlDatabase MyDB::db = QSqlDatabase();

#endif  // MyDB_H
