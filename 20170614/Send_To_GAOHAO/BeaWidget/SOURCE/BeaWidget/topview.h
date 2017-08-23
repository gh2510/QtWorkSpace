#ifndef TopView_H
#define TopView_H
#ifndef WIDTH
#define WIDTH 540
#endif
#ifndef HEIGHT
#define HEIGHT 500
#endif

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include "mygraphicspixmapitem.h"
#include <QMap>
#include <QString>
#include <QMutex>

namespace Ui {
class TopView;
}

#include "switch_info_stru.h"
class TopView : public QGraphicsView
{
    Q_OBJECT

public:
    TopView(QWidget *parent = 0);
    void addline(int startpix,int stoppix);
    void save_to_file();
    ~TopView();
signals:
    void signal_switchSelected(QString,QString);
    void signal_moving(QPoint pos);
    void signal_update();
    void signal_disconnected(QString);
   // void sig_alarm( QString );

public slots:
    void slot_ChangePixItem(int switchnumber,int alarmlevel);
    void slot_SeletedSwitchNumber();
    void slot_add_switcher();
    void slot_delete();
    void slot_connect();
    void slot_moving(QPoint pos);
    void slot_init();
    void slot_setAlarmSwitch(QString switchName,QString alarmType,QString value);
    void slot_setNormalSwitch(QString switchName);
    void slot_portStatus(QString,int ,int);
    bool checkRelatePort(QString nameA, QString nameB);

protected:

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *);

private:

    QPixmap normalswitchpix;        //接入层交换机图标
    QPixmap warningswitchpix;
    QPixmap breakswitchpix;

    QPixmap normalswitchpix_core;        //核心层交换机图标
    QPixmap warningswitchpix_core;
    QPixmap breakswitchpix_core;

    QGraphicsScene *scene;
    QMap<QString,Switcher*> m_switch_map;//交换机图标
    QMap<QString,QString> m_switch_port_map;//交换机理论连接信息
    QMap<QString,int*> portsState;//所有交换机端口状态
    QList<QGraphicsLineItem *> m_all_line;//交换机连线
    QList<QList<QString> > m_all_line_pos;//线坐标
    MyGraphicsPixmapItem * m_select_item;
    MyGraphicsPixmapItem * m_moving_item;
    bool is_press;
    QPointF cur_pos;
    QPointF move_last_pos;
    QPointF move_now_pos;

    QMutex mutex;
    Ui::TopView *ui;
};

#endif // TopView_H
