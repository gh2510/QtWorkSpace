#ifndef SELFCHECKTHREAD_H
#define SELFCHECKTHREAD_H

#include <QThread>
#include<QLibrary>
class SelfCheckThread : public QThread
{
    Q_OBJECT
public:
    explicit SelfCheckThread(QObject *parent = 0);
    ~SelfCheckThread();
    void run();
    bool flag;
signals:
    void sig_selfCheck(int status);//1故障，0正常
    
public slots:

private:
    QLibrary *selfCheck;

    
};

#endif // SELFCHECKTHREAD_H
