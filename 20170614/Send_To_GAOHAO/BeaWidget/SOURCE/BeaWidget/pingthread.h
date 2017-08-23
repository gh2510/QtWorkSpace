#ifndef PINGTHREAD_H
#define PINGTHREAD_H

#include <QObject>
#include<QProcess>
#include<QThread>
#include<QRegExp>
#include<QTextCodec>
#include<QDebug>
class PingThread : public QThread
{
    Q_OBJECT
public:
    PingThread(QObject *parent=0);
    QProcess *cmd;
public slots:
    void setList(QStringList list);

private slots:
    void processData();
signals:
    void pingSuccess(QString ip);
   // void pingFinished();
    void pingNum(int num);
protected:
    void run();
private:
    QStringList ipList;

    QByteArray temp;
    QTextCodec *codec;
    QRegExp *rx;

};



#endif // PINGTHREAD_H
