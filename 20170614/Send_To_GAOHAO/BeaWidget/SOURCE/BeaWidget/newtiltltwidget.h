#ifndef NEWTILTLTWIDGET_H
#define NEWTILTLTWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QTimer>
#include <QDateTime>
class QPixmap;

#include"selfcheckthread.h"

namespace Ui {
class newTiltltWidget;
}

class newTiltltWidget : public QWidget
{
    Q_OBJECT

public:
    explicit newTiltltWidget(QWidget *parent = 0);
    ~newTiltltWidget();
   void translatelanguage();
   void initShow();
   void turnFirstPage(int index);
   void changeUser(); //改变用户角色 yangmeng161022
   void initWidgetShow();

protected:
    bool eventFilter(QObject *, QEvent *);

signals:
    void showSkin();
    void showMin();
    void showMainMenu();
    void closeMainWindow();
    void minizeWindow();
    void turnpage(int current_page);
    void ifAlarmChanged(bool);

public slots:
   void turnpage();
   void selfCheckState(int status);
   void closeBtn_timestart();//“退出”按钮延时响应 yangmeng 161021
   void closeBtn_timestop();//“退出”按钮延时响应 yangmeng 161021
   void closeBtn_count();//“退出”按钮延时响应 yangmeng 161021
   void showCurTime();
   void slot_checkIcon(QString buttonName);   //切换标题按钮样式

private:
    Ui::newTiltltWidget *ui;

    bool ifOpen;
    bool showColon;
    int closeBtn_time;    
    QTimer *closeBtnTimer;
    QTimer *curTimeShowTimer;    
    QDateTime startDateTime;
    SelfCheckThread *selfCheck;
    QList<QToolButton *> button_list;
    void initPixMap();
//    QPixmap *facility;
};

#endif // NEWTILTLTWIDGET_H
