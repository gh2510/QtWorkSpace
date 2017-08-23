#ifndef TITLE_WIDGET_H
#define TITLE_WIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QPaintEvent>
#include "pushbutton_diy.h"
#include "toolbutton_diy.h"
#include "main_menu.h"
#include "statebar.h"
#include"selfcheckthread.h"

class TitleWidget :public QWidget
{
    Q_OBJECT
public :
    explicit TitleWidget(QWidget * parent=0);
    ~TitleWidget();
    void translatelanguage();

    void changeUser(); //改变用户角色 yangmeng161022
protected:
    void paintEvent(QPaintEvent *);
signals:
    void showSkin();
    void showMin();
    void showMainMenu();
    void closeMainWindow();
    void minizeWindow();
    void turnpage(int current_page);

public slots:
    void turnpage(QString current_page);
    void selfCheckState(int status);
    void closeBtn_timestart();//“退出”按钮延时响应 yangmeng 161021
    void closeBtn_timestop();//“退出”按钮延时响应 yangmeng 161021
    void closeBtn_count();//“退出”按钮延时响应 yangmeng 161021

private:
    QPoint press_point;
    bool is_move;
    QLabel *localState;
    QLabel *stateLight;
    QHBoxLayout *button_layout;
    QSignalMapper * signal_mapper;
    QVBoxLayout *main_layout;
    QPainter * painter;
    StateBar  *time_bar;
    QList<ToolButtonDiy *> button_list;
    SelfCheckThread *selfCheck;
    QStringList str_list;

    QTimer *closeBtnTimer;
    int closeBtn_time;
};


#endif // TITLE_WIDGET_H
