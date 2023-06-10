#pragma once
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

/**
 * @brief Класс DB предоставляет функции для работы с базой данных.
 */
class DB {
 public:
  /**
   * @brief Возвращает экземпляр класса DB (singleton).
   * @return Экземпляр класса DB.
   */
  static DB &getInstance();

  // Переменная для хранения базы данных
  static QSqlDatabase db;

  /**
   * @brief Инициализирует базу данных, открывает соединение и создает таблицы.
   */
  static void init();

  /**
   * @brief Закрывает соединение с базой данных.
   */
  static void close();

  /**
   * @brief Выполняет запрос на вставку данных в таблицу.
   * @param queryString Строка с SQL-запросом для вставки данных.
   * @return true, если запрос выполнен успешно, иначе false.
   */
  static bool insertData(const QString &queryString);

  /**
   * @brief Выполняет запрос и возвращает результаты в виде QMap.
   * @param request Строка с SQL-запросом для получения данных.
   * @return Результаты запроса в виде QMap.
   */
  static QMap<QString, QVariant> getData(const QString &request);

  /**
   * @brief Выполняет запрос и возвращает результаты в виде QSqlQuery.
   * @param request Строка с SQL-запросом для получения данных.
   * @return Результаты запроса в виде QSqlQuery.
   */
  static QSqlQuery getQsqlData(const QString &request);

  /**
   * @brief Создает запрос на вставку данных в таблицу.
   * @param data QMap с данными для вставки.
   * @return true, если запрос выполнен успешно, иначе false.
   */
  static bool makeInsertQuery(
      const QMap<QString, QMap<QString, QVariant>> &data);

  /**
   * @brief Получает какой id был вставлен последним.
   * @return id последней вставленной записи.
   */
  static int getLastInsertId();

  /**
   * @brief Создает таблицы в базе данных.
   */
  static void createTables();

  /**
   * @brief Удаляет таблицы из базы данных.
   */
  static void dropTables();

 protected:
  // DB();
  //~DB();

 private:
  friend class DBDestroyer;

  /**
   * @brief Открывает соединение с базой данных, если оно еще не открыто.
   */
  static void open();
};

/**
 * @brief Класс DBDestroyer управляет удалением экземпляра класса DB.
 */
class DBDestroyer {
 public:
  /**
   * @brief Конструктор класса DBDestroyer.
   * @param p_instance Указатель на экземпляр класса DB.
   */
  DBDestroyer(DB *p_instance);

  /**
   * @brief Деструктор класса DBDestroyer. Удаляет экземпляр класса DB.
   */
  ~DBDestroyer();

 private:
  DB *p_instance;
};
