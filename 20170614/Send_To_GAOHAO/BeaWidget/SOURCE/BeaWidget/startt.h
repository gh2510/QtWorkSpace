#ifndef STARTT_H
#define STARTT_H

#include <QObject>
#include <QMouseEvent>
#include <QTimerEvent>

class StartT : public QObject
{
    Q_OBJECT
public:
    StartT(QObject *parent = 0);
    int init_st();
    ~StartT();
private:
    int myTimerId;  
};

#endif // STARTTIMER_H
