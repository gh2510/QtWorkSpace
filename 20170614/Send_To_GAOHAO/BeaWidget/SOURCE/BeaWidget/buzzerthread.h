#ifndef BUZZERTHREAD_H
#define BUZZERTHREAD_H

#include <QThread>
#include<QMutex>

class buzzerThread : public QThread
{
    Q_OBJECT
public:
    explicit buzzerThread(QObject *parent = 0);

    void run();
    void setIfAlarm(bool);

signals:
    
public slots:
    void slot_buzzerCount();
private:
    int count;
    bool ifAlarm;
    QMutex mutex;
};

#endif // BUZZERTHREAD_H
