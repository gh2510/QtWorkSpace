#ifndef ALARMHISTORY_H
#define ALARMHISTORY_H

#include <QWidget>
#include "mypagetableview.h"
#include "search_alarm.h"
#include "qdebug.h"

class alarmHistory : public QWidget
{
    Q_OBJECT

public:
    explicit alarmHistory(QWidget *parent = 0);
    ~alarmHistory();
public slots:
    void slot_search_res(QString,QString,QString,QString,QString);

private:
     MyPageTableview *alarmTable;
     QVBoxLayout *main_layout;
     search_alarm *searchAlarm;
     QString pre_sql;
     QStringList ql;
     QList<int> qi;

};

#endif // ALARMHISTORY_H
