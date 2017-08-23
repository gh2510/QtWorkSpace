#ifndef PORTFLOWWATCH_H
#define PORTFLOWWATCH_H

#include <QWidget>
#include <QTabWidget>
#include "portplot.h"
#define SWITCHNUM  60//交换机端口数量

class PortFlowWatch : public QWidget
{
    Q_OBJECT
public:
    explicit PortFlowWatch(QWidget *parent = 0);
    void initWidget();
    void refresh_port();
    ~PortFlowWatch();
signals:

public slots:
    void slot_setswitchnum(QString  name);
    void slot_updateData(QString name,int portnum=1,double cpuusage=0,double memusage=0);

private:
    PortPlot port[SWITCHNUM];
    QString current_switch_name;
    QTabWidget *tabWidget;
};

#endif // PORTFLOWWATCH_H
