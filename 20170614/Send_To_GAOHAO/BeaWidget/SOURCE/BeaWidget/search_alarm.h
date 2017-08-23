#ifndef SEARCH_ALARM_H
#define SEARCH_ALARM_H

#include <QWidget>
#include <QSqlTableModel>

#include <QPushButton>
#include <QLineEdit>
#include <QMouseEvent>
#include <dateedit.h>
#include "calendar_dialog.h"
#include "labelcombox.h"
#include "commonbutton.h"
class search_alarm : public QWidget
{
    Q_OBJECT

public:
    explicit search_alarm(QWidget *parent = 0);
    ~search_alarm();

public slots:
   void  slot_search();
   void slot_clearTime();
   void slot_clearData();
signals:
    void signal_search(QString,QString,QString,QString,QString);

private:
     QSqlTableModel * alarmtablemodel;
     DateEdit *starttime;
     DateEdit *endtime;
     LabelComBox *isConfirmed;
     QLabel *label5;
    commonButton *clearTime;   //, *clearData;
     commonButton *search;
     commonButton *clearData;  //清空数据按钮

     LabelComBox *switchName;
     LabelComBox *alarmClass;
     QVBoxLayout *main_layout ;
     int flag;
};

#endif // SEARCH_ALARM_H
