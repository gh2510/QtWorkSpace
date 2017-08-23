#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <qstackedwidget.h>
#include <qstackedlayout.h>
#include <QTabWidget>
#include "myplot.h"
#include "myflashlist.h"
#include "switchthread.h"
#include "portflowwatch.h"
#include "insertthread.h"
#include "newportflowwatch.h"

namespace Ui {
class MonitorWidget;
}

class MonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget *parent = 0);
    ~MonitorWidget();
public slots:
    void slot_init_widget();
    void slot_switchWarning(QString switchName,QString alarmType,QString value);

signals:
    void sig_warningToTop(QString switchName,QString alarmType,QString value);
    void sig_portStatus(QString,int ,int);
    void sig_version(QString switchName,QString version);
    void sig_setNormal(QString switchname);

private:
    QTabWidget *tabWidget;
    Ui::MonitorWidget *ui;
    myFlashList *flashlist;
    MyPlot * cpumemplot;
//    PortFlowWatch *portswatch;
    NewPortFlowWatch *portswatch;
    InsertThread *insert;
   // SwitchThread * switchthread[12];
    int switch_num;

    public:
     QList<SwitchThread*> swi_thread_list;
};

#endif // MONITORWIDGET_H
