#include "mydb.h"
#include "tcpserver.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication serverApp(argc, argv);
  MyDB::createDB();
  MyTcpServer server;

  return serverApp.exec();
}
