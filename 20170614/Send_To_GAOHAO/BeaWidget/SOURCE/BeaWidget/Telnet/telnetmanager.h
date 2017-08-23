#ifndef TELNETMANAGER_H
#define TELNETMANAGER_H

#include "telnet.h"
#include <QList>
#include <QSemaphore>
#include <QMutex>
#define REC_NOMAL 0
#define REC_QUERY 1
class telnetManager:public QThread
{   
    Q_OBJECT
public:
    telnetManager();
    ~telnetManager();

    int connToServerandInit(QString ob_ip,QString tel_pass,QString t_pass);
    int sendCmd(QString cmd);
    void copeWithMore(QString txt_recv);
    void close_telnet();
    void set_read_mode(int);
    int get_tel_status();
    void run();
signals:
    void readServer(QString msg);
    void signal_discon();
    void signal_error();
public slots:
    void confVlan(QString vlanId,QString ip,QList<int> portList);
    void query(QString vlanId);
    void read_server();
    void confPort(int port,QString portStatus,QString portMode,QString portSpeed);
    void doRead();

private:
    Telnet *telnet;
    QString txt_recv;
    QList<QString> commands;
    QSemaphore sem;
    QMutex mutex;
    QMutex inMutex;
    QMutex runningMutex;
    int flag;
    bool incomeing;
    bool running;
    int tel_status;
};

#endif // TELNETMANAGER_H
