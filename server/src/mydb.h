#ifndef MyDB
#define MyDB

#include <QCoreApplication>

#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "singleton.h"

class MyDB : public Singleton
{
private:
    MyDB() = delete;
    MyDB(const MyDB &Db) = delete;
     QSqlDatabase db;

     void openDB(){
        qDebug()<<"MyDB()\n";
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Test");
        if(!db.open())
            qDebug()<<db.lastError().text();
    }
public:
     QString query_select(){
         QSqlQuery query = QSqlQuery(db);
        query.exec("SELECT * FROM User");
        if (query.next()) {
            QSqlRecord rec = query.record();
            const int loginIndex = rec.indexOf("login");//номер "столбца"
            const int passwordIndex = rec.indexOf("password");
            return query.value(loginIndex).toString()+" "+query.value(passwordIndex).toString();
        } else
            return "Sorry, something went wrong";
    }

     void createDB(){
        Singleton::getInstance();
        if (!db.isOpen())
        {
            openDB();
        }

    }
     void close(){
        if(db.isOpen())
            db.close();
    }
};
QSqlDatabase MyDB::db;

#endif
