#ifndef SIGLE_TOPO_INFO_H
#define SIGLE_TOPO_INFO_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QTableView>
#include <QStandardItemModel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include "labeledit.h"
#include "switchstateview.h"
#include "loopview.h"
#include "mystandarditemmodel.h"
#include"commonbutton.h"
#include <QMap>
#include"switchinfodialog.h"

namespace Ui {
class sigle_topo_info;
}

class sigle_topo_info : public QWidget
{
    Q_OBJECT

public:
    explicit sigle_topo_info(QWidget *parent = 0);
    ~sigle_topo_info();

public slots:
    void  slot_switchSelected(QString,QString );
     void slot_portStatus(QString,int ,int);
     void slot_version(QString name,QString version);
     void slot_showInfo();
     void slot_sig_alarm(QString switchname);
protected:
//   virtual void paintEvent(QPaintEvent * e);
    void initWidget();
    void initTableWidth(); // 设置告警表格宽
private:
    commonButton *info_button;
    QLabel  * m_name;
    LabelEdit  * m_location;
    LabelEdit  * m_leIP;
    LabelEdit  * m_lestate;
    myStandardItemModel *tbInfoModel;
    QTableView * tb_info;
    SwitchStateView * ssv;
    LoopView *loopv;
    int switchType;
    QString switchName;
    QMap<QString,int*> portsState;
    QMap<QString,QString> versionMap;       //yangmeng 161026 缓存版本信息
    QVBoxLayout *main_layout;
    SwitchInfoDialog *dialog;
    Ui::sigle_topo_info *ui;
};

#endif // SIGLE_TOPO_INFO_H
