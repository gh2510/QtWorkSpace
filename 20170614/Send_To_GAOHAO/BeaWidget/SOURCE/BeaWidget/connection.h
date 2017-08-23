#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <qmessagebox.h>
#include <qsqlerror.h>

class DBConnection{

public:
    static QSqlDatabase db;
    static bool createConnection()
    {
       // db= QSqlDatabase::addDatabase("QSQLITE","1");
        db.setDatabaseName("data.db");
        if(!db.open()){
            //提示出错
            QMessageBox::critical(0, QObject::tr(" 连接数据库data.db失败！ "), db.lastError().text());
            return false;
        }


        return true;
    }


};

#endif // CONNECTION_H
