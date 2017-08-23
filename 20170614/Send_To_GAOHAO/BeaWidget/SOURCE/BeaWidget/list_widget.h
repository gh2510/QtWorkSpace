#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QPaintEvent>
#include "ListButton.h"



class ListWidget :public QWidget
{
    Q_OBJECT
public :
    explicit ListWidget(QWidget * parent=0);
    ~ListWidget();
    void translatelanguage();

    void changeUser();      //改变用户角色 yangmeng 161022
signals:

    void turnpage(int current_page);
public slots:
    void turnpage(QString current_page);

private:
    void paintEvent(QPaintEvent *);
    QPoint press_point;
    bool is_move;
    QVBoxLayout *button_layout;
    QSignalMapper * signal_mapper;

    QList<ListButton *> button_list;

    QStringList str_list;   //yangmeng 161022 修改用户角色切换问题，将局部变量改为成员变量
};


#endif // LIST_WIDGET_H
