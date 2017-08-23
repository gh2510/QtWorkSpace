#ifndef MAINVIEW_H
#define MAINVIEW_H
#include "alarmtableview.h"
#include "topview.h"
#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include "list_widget.h"
#include "switcher_topo.h"
#include "switch_conf.h"
#include "newlistwidget.h"
#include "newalarmhistory.h"
#include "newswitchmanage.h"
#include "newcapturdialog.h"
class QSplashScreen;

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0,QSplashScreen *splash=0);
    switcher_topo *st;
    NewAlarmHistory  *ah;
    NewSwitchManage *switchmanage;
    switch_conf *sc ;
    NewCapturDialog *cdg;

    ~MainView();

    void changeUser();      //改变用户角色 yangmeng 161022
signals:
    void signal_indexchange(int index);

public slots:
    void slot_indexchange(int index);

private:
    Ui::MainView *ui;

    QStackedWidget  *stack_widget;
    NewListwidget *optionList;
    void initOptionView();
    void createsSwitcher_Topo();
    void createNewAlarmHistory();
    void createNewSwitchManage();
    void createSwitch_Conf();
};

#endif // MAINVIEW_H
