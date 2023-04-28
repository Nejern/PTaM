#include <db.h>

DB::DBDestroyer::DBDestroyer(DB *p_instance) { this->p_instance = p_instance; };

DB::DBDestroyer::~DBDestroyer() { delete p_instance; };

void DB::open() {
  if (db.isOpen()) {
    return;
  }
  qDebug() << "MyDB()\n";
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("Test.sql");
  if (!db.open())
    qDebug() << db.lastError().text();
};

DB &DB::getInstance() {
  static DB instance;
  return instance;
};

void DB::init() {
  getInstance();
  open();
  createTables();
};

void DB::close() {
  if (db.isOpen()) {
    db.close();
  }
};

bool DB::insertData(const QString &queryString) {
  open();
  QSqlQuery query(db);
  query.exec("PRAGMA foreign_keys = ON");
  // Выполнение запроса
  if (!query.exec(queryString)) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    return false;
  }
  return true;
};

QMap<QString, QVariant> DB::getData(const QString &request) {
  QMap<QString, QVariant> resultMap;

  // Открытие базы данных
  open();

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
};

bool DB::makeInsertQuery(const QMap<QString, QMap<QString, QVariant>> &data) {
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
};

void DB::createTables() {
  QSqlQuery query(db);
  query.exec("PRAGMA foreign_keys = ON");
  insertData("CREATE TABLE IF NOT EXISTS roles ("
             "role_id INT PRIMARY KEY,"
             "role TEXT"
             ");");
  insertData("CREATE TABLE IF NOT EXISTS users ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
             "login TEXT,"
             "password TEXT,"
             "role_id INT"
             ");");

  insertData("CREATE TABLE IF NOT EXISTS grades ("
             "student_id INT,"
             "excercise INT,"
             "grade INT"
             ");");
  insertData("CREATE TABLE IF NOT EXISTS students ("
             "id INT,"
             "firstname TEXT,"
             "surname TEXT,"
             "patronymic TEXT,"
             "studygroup TEXT"
             ");");
};

void DB::dropTables() {
  insertData("DROP TABLE IF EXISTS users;");
  insertData("DROP TABLE IF EXISTS roles;");
  insertData("DROP TABLE IF EXISTS students;");
  insertData("DROP TABLE IF EXISTS grades;");
};

QSqlDatabase DB::db;
