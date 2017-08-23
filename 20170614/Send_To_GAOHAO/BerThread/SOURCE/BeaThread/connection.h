#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <qmessagebox.h>
#include <qsqlerror.h>
#include <QDebug>

class DBConnection{

public:
    static QSqlDatabase db;
    static bool createConnection()
    {
       // db= QSqlDatabase::addDatabase("QSQLITE","1");
        db.setDatabaseName("data.db");
        if(!db.open()){
            //提示出错
            QMessageBox::critical(0, QObject::tr(" 连接数据库失败！ "), db.lastError().text());
            return false;
        }else {
            qDebug()<<__FILE__<<__LINE__<<"\n"
                   <<"connect data.db Successed"
                   <<"\n";
        }

        return true;
    }


};

#endif // CONNECTION_H
