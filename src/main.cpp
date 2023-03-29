#include "tcpserver.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication serverApp(argc, argv);

  MyTcpServer server;

  return serverApp.exec();
}
