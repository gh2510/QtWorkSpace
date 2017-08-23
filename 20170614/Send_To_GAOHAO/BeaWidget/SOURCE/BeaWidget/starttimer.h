#ifndef STARTTIMER_H
#define STARTTIMER_H

#include <QObject>
#include <QMouseEvent>
#include <QTimerEvent>

class StartT : public QObject
{
    Q_OBJECT
public:
    explicit StartT(QObject *parent = 0);
    ~StartT();
private:
    int myTimerId;  
};

#endif // STARTTIMER_H
