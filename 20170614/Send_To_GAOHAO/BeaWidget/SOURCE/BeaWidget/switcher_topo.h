#ifndef SWITCHER_TOPO_H
#define SWITCHER_TOPO_H

#include <QWidget>
#include <QLabel>
#include "alarmtableview.h"
#include "topview.h"
#include  "switchstateview.h"
#include "sigle_topo_info.h"
#include <QDir>
#include <fstream>

namespace Ui {
class switcher_topo;
}

class switcher_topo : public QWidget
{
    Q_OBJECT

public:
    explicit switcher_topo(QWidget *parent = 0);
    ~switcher_topo();
    TopView *topview;
    sigle_topo_info *alarmtableview;
public slots:
     void slot_portStatus(QString,int ,int);
private:
    Ui::switcher_topo *ui;

    //SwitchStateView *m_ssv_sw1;
    SwitchStateView *m_ssv_sw2;
    SwitchStateView *m_ssv_sw3;
   // SwitchStateView *m_ssv_sw4;
    QMap<QString,int*> portsState;
    QHBoxLayout *sv_h_layout;
    QVBoxLayout *left_layout;
    QHBoxLayout *topinfo_layout;
    int currentNum;
    QString logFileName;
signals:
    void signal_addRecord(QString);     //yangmeng 161026 日志记录核心交换机端口变化
};

#endif // SWITCHER_TOPO_H
