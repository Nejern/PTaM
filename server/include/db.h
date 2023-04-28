#pragma once
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class DB {
public:
  static DB &getInstance();

  // Переменная для хранения базы данных
  static QSqlDatabase db;

  // Функция для создания базы данных
  static void init();

  // Функция для закрытия базы данных
  static void close();

  // Функция для выполнения запроса на вставку данных в таблицу
  static bool insertData(const QString &queryString);

  // Функция для выполнения запроса и получения результатов в виде QMap
  static QMap<QString, QVariant> getData(const QString &request);

  // Функция для составления запроса на вставку данных в таблицу
  static bool
  makeInsertQuery(const QMap<QString, QMap<QString, QVariant>> &data);

  // Функция для создания таблиц
  static void createTables();

  // Функция для удаления таблиц
  static void dropTables();

protected:
  // DB();
  //~DB();

private:
  class DBDestroyer {
  public:
    DBDestroyer(DB *p_instance);
    ~DBDestroyer();

  private:
    DB *p_instance;
  };

  friend class DBDestroyer;

  static void open();
};
