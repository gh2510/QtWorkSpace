#include "pingthread.h"
#include<QTextCodec>
#include<QDebug>
PingThread::PingThread(QObject *parent):
     QThread(parent)
{
}

void PingThread::setList(QStringList list)
{
    ipList=list;
}

void PingThread::processData()
{
    temp=cmd->readAll();
    QString tempIP;
    QString output=codec->toUnicode(temp);
   // qDebug()<<"fanhuizhi : "<<output<<endl;
    if(output.contains("TTL",Qt::CaseInsensitive))
    {
       int pos=output.indexOf(*rx);
       if(pos>=0)
       {
           int len=rx->matchedLength();
           tempIP=output.mid(pos,len);
           emit pingSuccess(tempIP);
       }
    }
}

void PingThread::run()
{
    //在QThread中定义的所有东西都属于创建该QThread的线程。
    //所以在构造函数中初始化的cmd应该是属于父线程的，那么在run中调用时就属于跨线程调用。
    //所以把cmdt放到run中初始化就属于线程的了，调用时就不会出现跨线程调用的问题。
    cmd=new QProcess;
    codec = QTextCodec::codecForName("GB18030");
    //明明定义了槽却找不到的原因是没有声明Q_OBJECT
    connect(cmd,SIGNAL(readyRead()),this,SLOT(processData()),Qt::DirectConnection);
    rx=new QRegExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    QString ip;
    QString commond;
    int count=0;
    foreach(ip,ipList)
    {
        commond="ping "+ip+" -n 1";
        qDebug()<<"run"<<commond<<endl;
        cmd->start(commond);
        //cmd->waitForStarted();
        cmd->waitForFinished();//这句很关键，不然没有返回值
        //cmd->execute(commond);
        count++;
        emit pingNum(count);

    }

}

