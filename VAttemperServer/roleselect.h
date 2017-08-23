#ifndef ROLESELECT_H
#define ROLESELECT_H

#include <QWidget>
#include "configparse.h"
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include "attemperform.h"
#include <QTextEdit>

/*
 *
 *类说明：界面类。负责根据配置文件，显示角色选择类
 *
 *
 */

namespace Ui {
class RoleSelect;
}

class RoleSelect : public QWidget
{
    Q_OBJECT
    
public:
    explicit RoleSelect(QWidget *parent = 0);
    ~RoleSelect();
    void InitWidget(ConfigParse &configParse); // 根据配置文件信息初始化窗口显示
    void UpdateWidget();  // 当返回上一级时，根据当前的角色信息更新显示窗口
    
public slots:
    void okbtn_click(); // 点击确定响应事件
    void cancelbtn_click(); // 点击退出响应事件
    void checkbox_click(bool checked); // 点击角色响应事件
private:
    Ui::RoleSelect *ui;
    QPushButton *okButton; // 确定按钮
    QPushButton *cancelButton; // 退出按钮
    QButtonGroup *checkboxGroup;
    QList<CheckBoxInfo> checkInfoList; // 所有复选框对象
    AttemperForm *attemperForm;
    QTextEdit *descriptionedit; // 显示角色描述信息的文本对象
};

#endif // ROLESELECT_H
