#ifndef NEWPORTFLOWWATCH_H
#define NEWPORTFLOWWATCH_H

#include <QWidget>
#include "portplot.h"
#define SWITCHNUM  60//交换机端口数量

namespace Ui {
class NewPortFlowWatch;
}

class NewPortFlowWatch : public QWidget
{
    Q_OBJECT

public:
    explicit NewPortFlowWatch(QWidget *parent = 0);
    ~NewPortFlowWatch();
    void initWidget();
    void refresh_port();

public slots:
    void slot_setswitchnum(QString  name);
    void slot_updateData(QString name,int portnum=1,double cpuusage=0,double memusage=0);

private:
    Ui::NewPortFlowWatch *ui;
    PortPlot port[SWITCHNUM];
    QString current_switch_name;
    QList <QWidget *> pages;
    QStringList pageName;
};

#endif // NEWPORTFLOWWATCH_H
