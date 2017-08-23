#include "starttimer.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include"connection.h"

StartT::StartT(QObject *parent) :
    QObject(parent)
{   
    myTimerId = StartTimer(3000);
}
StartT:: ~StartT()
{
    KillTimer (myTimerId);
    myTimerId = 0;
}

