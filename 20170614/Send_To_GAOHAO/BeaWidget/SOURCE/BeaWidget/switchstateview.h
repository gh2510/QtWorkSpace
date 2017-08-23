#ifndef SWITCHSTATEVIEW_H
#define SWITCHSTATEVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <qmath.h>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>

#define SWITCH_NUM 60
#define LINE_NUM  12


// gaohao Modify
enum SwitchState
{
       switchTest, // 测试
       switchUp, // 启动
       switchDown,  // 关闭
       switchWarn // 警告
};

//#define GREEN_STATE  1
//#define RED_STATE    0
//#define GRAY_STATE   2 //

#define TTM      60   //48+12
#define FETM     52   //48+4
#define TFTM     28  //24+4

namespace Ui {
class SwitchStateView;
}

class SwitchStateView : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchStateView(QWidget *parent = 0);
     ~SwitchStateView();
    void setTitle(QString title);
    void setSwitchType( int );
    QList<QLabel *> pix_list;
    QPixmap *switch_pix_green;
    QPixmap *switch_pix_red;
    QPixmap *switch_pix_gray;
    QPixmap *switch_pix_yellow;

protected:
     virtual void paintEvent(QPaintEvent * event);

signals:

public slots:
    void change_port_state(int port_id,int state);

private:
    QList<QLabel *> txt_list;
    QLabel  *lbltitle;
    QVBoxLayout *v_layout;
    Ui::SwitchStateView *ui;
};

#endif // SWITCHSTATEVIEW_H
