#ifndef INSERTTHREAD_H
#define INSERTTHREAD_H

#include <QThread>
#include <QSqlQuery>
#include <QVariant>
#include<QSqlError>
#include<QtSql>
extern QSqlDatabase db_sqlite;
class InsertThread : public QThread
{
    Q_OBJECT
public:
    explicit InsertThread(QObject *parent = 0);
    ~InsertThread();
    void run();

private:

QSqlQuery  *query;

int count;
signals:
    
public slots:
    void insert_cpu_men(QString type,double value,QString state,QString name);
    void insert_portSpeed(QString type,double value,QString state,QString name);
    void insert_portState(QString type,double value,QString state,QString name);

    void sig_cpu_mem_deal(QString type,double value,QString state,QString name); // gaohao 1031 Add 该信号用于处理CPU和内存的正常状态


};

#endif // INSERTTHREAD_H
