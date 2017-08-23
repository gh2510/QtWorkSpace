#ifndef ATTEMPERFORM_H
#define ATTEMPERFORM_H

#include <QHBoxLayout>
#include <mainwindow.h>
#include <combatposition.h>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

/*
 * 类说明： 调度窗口类。负责显示调度界面框架，允许用户切换角色，实现页面调度。同时可以返回到之前的站位
 * 创建人： 高暠
 *
 *
 */
#include <QWidget>

namespace Ui {
class AttemperForm;
}

class AttemperForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AttemperForm(QWidget *frontWidget,QWidget *parent = 0);
    void UpdateForm(); // 更新界面上的信息
    void InitWidget();
    ~AttemperForm();

public slots:
    void resbtn_click(); // 点击返回上一级事件
    void exitbtn_click(); // 点击退出的事件
    void indexChanged(const QString &text);  // 切换角色的事件
    
private:
    Ui::AttemperForm *ui;
    QLabel *cpLabel;  // 站位信息
    QComboBox *rlCombox; // 角色列表
    QPushButton *retBtn; // 返回上一级按钮
    QPushButton *exitBtn; // 退出按钮
    QWidget *frontWidget; // 打开本窗口的上一级窗口

};

#endif // ATTEMPERFORM_H
