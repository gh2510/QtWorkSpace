#include "attemperform.h"
#include "roleselect.h"
#include "ui_attemperform.h"
#include <QDesktopWidget>

AttemperForm::AttemperForm(QWidget *frontWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttemperForm)
{
    this->frontWidget = frontWidget;
    ui->setupUi(this);
}

AttemperForm::~AttemperForm()
{
    delete ui;
}


/*
 * 函数名称：InitWidget
 * 函数功能：负责根据当前用户选择的站位，初始化窗口
 * 参数：
 *      无
 *  返回值：
 *       无
 *
 */
void AttemperForm::InitWidget()
{
    setWindowFlags(Qt::FramelessWindowHint);
    // 设置窗口的位置，获得屏幕的分辨率
    int screenW = qApp->desktop()->screen()->width();
    int screenH = qApp->desktop()->screen()->height();
    float hlvt = 0.9f;
    this->setGeometry(0, 0 ,screenW, screenH * (1.0f-hlvt)); // screenH * hlvt
    CombatPosition combatPosition = MainWindow::currentCombatPosition;
    // 选择布局模式
    QHBoxLayout *layout = new QHBoxLayout;  //创建按钮的布局对象
    // 创建站位

    int textWidth = 120; // 一般控件的宽度

    QLabel *cpLabelSign = new QLabel("当前战位：");
    cpLabelSign->setAlignment(Qt::AlignCenter);
    cpLabelSign->setFixedWidth(textWidth);
    layout->addWidget(cpLabelSign);
    cpLabel = new QLabel(combatPosition.estradeName);
    cpLabel->setFixedWidth(textWidth);
    cpLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(cpLabel);

    // 创建角色
    QLabel *rlLabelSign = new QLabel("当前角色：");
    rlLabelSign->setAlignment(Qt::AlignCenter);
    rlLabelSign->setFixedWidth(textWidth);
    layout->addWidget(rlLabelSign);
    // 创建下拉框
    rlCombox = new QComboBox();
    for(int i=0;i<combatPosition.roleList.count();i++)
    {
        rlCombox->addItem(combatPosition.roleList.at(i).getRoleName());
    }
    connect(rlCombox,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(indexChanged(const QString&)));
    layout->addWidget(rlCombox);
    rlCombox->setFixedWidth(textWidth);
    // 添加一个弹簧控件
    layout->addStretch(3);
    // 添加一组按钮
    retBtn = new QPushButton();
    retBtn->setText("返回");
    retBtn->setFixedWidth(90);
    layout->addWidget(retBtn);
    exitBtn = new QPushButton();
    exitBtn->setText("退出");
    exitBtn->setFixedWidth(90);
    layout->addWidget(exitBtn);

    setLayout(layout);

    // 关联事件
    connect(retBtn, SIGNAL(clicked()), this, SLOT(resbtn_click()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitbtn_click()));

}

/*
 * 函数名称：UpdateForm
 * 函数功能：更新站位、角色等信息
 * 参数：
 *     无
 * 返回值：
 *      无
 *
 */
void AttemperForm::UpdateForm()
{
    CombatPosition combatPosition;
    combatPosition = MainWindow::currentCombatPosition;
    // 更新站位名称
    cpLabel->setText(combatPosition.estradeName);
    // 更新角色名称与列表
    rlCombox->clear();
     int index = -1;
    for(int i=0;i<combatPosition.roleList.count();i++)
    {
        if(index==-1&&combatPosition.roleList.at(i).getRoleName()==combatPosition.getCurRole().getRoleName())
            index = i;
        rlCombox->addItem(combatPosition.roleList.at(i).getRoleName());
    }
    rlCombox->setCurrentIndex(index);
}

void AttemperForm::resbtn_click()
{
    // 返回到上一级窗口
    this->hide();
    // 清空当前选择的信息
    ((RoleSelect*)frontWidget)->UpdateWidget();
    frontWidget->show();
}

void AttemperForm::exitbtn_click()
{
    exit(0);
}

/*
 *
 * 函数名称：indexChanged
 * 函数功能：角色的combo切换响应事件
 * 参数：
 *     text：切换的名称
 * 返回值：
 *     无
 *
 */
void AttemperForm::indexChanged(const QString& text)
{
    // 根据名称判断当前角色代号
    if(text == "") // 表示清空产生的事件
        return;
    Role role;

    for(int i=0;i<MainWindow::currentCombatPosition.roleList.count();i++)
    {
        role = MainWindow::currentCombatPosition.roleList.at(i);
        if(role.getRoleName() == text)
        {
            MainWindow::currentCombatPosition.SetCurRole(role);
            MainWindow::attmper->ChangeRole(MainWindow::currentCombatPosition); // 进行调度命令
            return;
        }
    }
}

