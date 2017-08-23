#ifndef GRAMMANAGE_H
#define GRAMMANAGE_H

#include <QWidget>
#include <QStackedWidget>
#include "listwidgetgram.h"
#include "alarmgram.h"
#include "alarmthreshset.h"
#include"errormanage.h"
#include"errordeal.h"
#include"showlogdialog.h"
#include"showloghistory.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

class NewAlarmThreshSet;
class NewErrorManage;
class NewShowLogDialog;
class NewShowLogHistory;
class NewListWidgetGram;

namespace Ui {
class GramManage;
}

class GramManage : public QWidget
{
    Q_OBJECT
public:
    explicit GramManage(QWidget *parent = 0);
    ~GramManage();
    void initWidget();
//    ErrorManage * errorManage;                                      //change
//    ShowLogDialog * logDialog;      //yangmeng 161026 日志实时更新    //change
//    showLogHistory * logHistory;    //qhy, 2016.11.29               //change
//    AlarmThreshSet *alarmthreshset;                                 //change

      NewErrorManage *errorManage;
      NewShowLogDialog *logDialog;
      NewShowLogHistory *logHistory;
      NewAlarmThreshSet *alarmthreshset;

signals:
    void signal_indexchange(int index);
    void signal_cancelWarning(QString switchName);
public slots:
    void slot_indexchange(int index);

private:
    Ui::GramManage *ui;
    QStackedWidget  *stack_widget;
   // AlarmGram      *alarmGram;

    ErrorDeal * errorDeal;
//    ListWidgetGram *optionList;//change
    NewListWidgetGram *optionList;
    QHBoxLayout *main_layout;
    void initOptionView();


};

#endif // GRAMMANAGE_H
