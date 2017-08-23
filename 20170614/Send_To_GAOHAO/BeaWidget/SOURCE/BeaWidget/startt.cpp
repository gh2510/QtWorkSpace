#include "startt.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include"connection.h"

StartT::StartT(QObject *parent) :
    QObject(parent)
{   
    myTimerId = init_st();
}
StartT:: ~StartT()
{
    killTimer (myTimerId);
    myTimerId = 0;
}

int StartT::init_st()
{
    return  startTimer(6000);
}
