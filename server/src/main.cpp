#include "db.h"
#include "tcpserver.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication serverApp(argc, argv);
  DB::init();
  MyTcpServer server;

  return serverApp.exec();
}
