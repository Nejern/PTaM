#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "mydb.h"
#include "tcpserver.h"

int main(int argc, char *argv[]) {
  QCoreApplication serverApp(argc, argv);
  MyDB::createDB();
  MyTcpServer server;

  return serverApp.exec();
}
