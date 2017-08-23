#ifndef SEARCH_PERFORMANCE_H
#define SEARCH_PERFORMANCE_H

#include <QWidget>
#include <QSqlTableModel>

#include <QPushButton>
#include <QLineEdit>
#include <QMouseEvent>
#include <dateedit.h>
#include "calendar_dialog.h"
#include "labelcombox.h"
#include "commonbutton.h"
namespace Ui {
class Search_performance;
}

class Search_performance : public QWidget
{
    Q_OBJECT
    
public:
    explicit Search_performance(QWidget *parent = 0);
    ~Search_performance();
    LabelComBox *port;
public slots:
   void  slot_search();
   void  slot_clear();
   void slot_clearTime();
   void slot_setPort(QString text);
signals:
    void signal_search(QString,QString,QString,QString,QString,QString);
     void signal_clear();
private:
     QSqlTableModel * alarmtablemodel;
     DateEdit *starttime;
     DateEdit *endtime;

     QLabel *label5;
     commonButton *search;
     commonButton *clear;
     commonButton *clearTime;
     LabelComBox *switchName;
     LabelComBox *alarmClass;
     LabelComBox *state;

     QVBoxLayout *main_layout ;
     int flag;

    Ui::Search_performance *ui;
};

#endif // SEARCH_PERFORMANCE_H
