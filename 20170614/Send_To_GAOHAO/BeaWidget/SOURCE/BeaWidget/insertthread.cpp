#include "insertthread.h"
#include<QDateTime>
#include "connection.h"
#include<QDebug>

QSqlDatabase db_sqlite=QSqlDatabase::addDatabase("QSQLITE","2");
InsertThread::InsertThread(QObject *parent) :
    QThread(parent)
{

    db_sqlite.setDatabaseName("data2.db");
    if(!db_sqlite.open())
    {
        qDebug()<<"insert data2.db open database failure";
    }
    else
         qDebug()<<"insert data2.db open database succes";

    if(db_sqlite.transaction())
         qDebug()<<"transaction succes";
    count=0;

    query=new QSqlQuery("",db_sqlite);

}

InsertThread::~InsertThread()
{
    delete query;
}

void InsertThread::run()
{
   // QSqlQuery  query("",db_sqlite);
}

/*
        gaohao 1031 Add 更新CPU和内存的处理状态
        alarmType = CPU温度过高 或者  内存使用率过高
        state = 正常 或 超限
        name：交换机名称
*/
void InsertThread::sig_cpu_mem_deal(QString alarmType, double value, QString state, QString name)
{
    // gaohao Add 当错误处理后，自动更新alarmCurrent数据库中的数据
    if(state == "正常")
    {
            QSqlQuery *mdbquery= new QSqlQuery("",DBConnection::db);
            QString update_sql = "update alarmcurrent set isdeal=? where name=? and alarmtype=? ";
             mdbquery->prepare(update_sql);
             mdbquery->bindValue(0,"是");
             mdbquery->bindValue(1,name);
             mdbquery->bindValue(2,alarmType);
             mdbquery->exec();
             mdbquery->finish();
             mdbquery->clear();
             delete mdbquery;
    }

}

void InsertThread::insert_cpu_men(QString type, double value, QString state, QString name)
{
    qDebug()<<"cpu_mem success: "<< type << "value: " << value <<"state:"<<state << endl;

    query->prepare("insert into performance (time,type,value,state,switchname) values (?,?,?,?,?)");
    query->bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query->bindValue(1,type);
    query->bindValue(2,value);
    query->bindValue(3,state);
    query->bindValue(4,name);
    query->exec();
    count++;
    if(count>=10000)
    {
        if(db_sqlite.commit())qDebug()<<"commit success "<<endl;;
        query->finish();
         query->clear();
        db_sqlite.transaction();
        count=0;
    }

}

void InsertThread::insert_portSpeed(QString type, double value, QString state, QString name)
{
   // qDebug()<<"portSpeed  success";

    query->prepare("insert into performance (time,type,value,state,switchname) values (?,?,?,?,?)");
    query->bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query->bindValue(1,type);
    query->bindValue(2,value);
    query->bindValue(3,state);
    query->bindValue(4,name);
    query->exec();
    count++;
    if(count>10000)
    {
        if(db_sqlite.commit())qDebug()<<"commit success "<<endl;
          //query->clear();
        db_sqlite.transaction();
        count=0;
    }
}

void InsertThread::insert_portState(QString type, double value, QString state, QString name)
{

      // qDebug()<<"portStateeeeeeeeeeeee success";
    query->prepare("insert into performance (time,type,value,state,switchname) values (?,?,?,?,?)");
    query->bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query->bindValue(1,type);
    query->bindValue(2,value);
    if(value==1)
    {
        query->bindValue(3,"UP");
    }
    else
    {
        query->bindValue(3,"DOWN");
    }

    query->bindValue(4,name);
    query->exec();
    count++;
    if(count>10000)
    {
        if(db_sqlite.commit())qDebug()<<"commit success "<<endl;;
         // query->clear();
        db_sqlite.transaction();
        count=0;
    }
}
