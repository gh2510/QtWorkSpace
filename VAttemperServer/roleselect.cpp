#include "roleselect.h"
#include "ui_roleselect.h"
#include "mainwindow.h"

RoleSelect::RoleSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoleSelect)
{
    ui->setupUi(this);
    attemperForm = NULL;
}

RoleSelect::~RoleSelect()
{
    delete ui;
}

/*
 * 函数名称：InitWidget
 * 函数功能：负责战位信息，动态生成界面，包括站位和角色
 * 参数：
 *     combatPosition：站位信息。
 * 返回值：
 *     无。
 *
 *
 */
void RoleSelect::InitWidget(ConfigParse &configParse)
{
    setWindowFlags(Qt::FramelessWindowHint);
    // 根据当前整个系统战位的数量，以及最大角色的数量，动态生成窗口宽度和高度
    int combatPositionNum = configParse.getCombatPositionNum();
    int maxRoleNum = configParse.getMaxRoleNum();

    if(combatPositionNum == 0)
    {
        QMessageBox::information(this,tr("错误提示"),tr("配置文件中未获得战位信息，请核实！"),QMessageBox::Ok);
        exit(0); // 直接退出的程序
    }
    if(maxRoleNum == 0)
    {
       QMessageBox::information(this,tr("错误提示"),tr("配置文件中未获得角色信息，请核实！"),QMessageBox::Ok);
        exit(0); // 直接退出的程序
    }

    // 生成宽度和高度，目前暂定每个站位占有的宽度为 50，两次宽度预留为 60。高度每个角色占有20，间隔为10，标题高度为0，上下空间为10
    int widgetWidth = 60*2 + combatPositionNum * 120;
    int widgetHeight = 50*2 + maxRoleNum * 40 + (maxRoleNum-1) * 30 + 40;

    setFixedSize(widgetWidth,widgetHeight);

    // 设置整个窗口的layout，窗口分为三部分，标题栏、角色选择区以及退出按钮
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // 显示标题栏
    QLabel *label = new QLabel(tr("服务化调度系统客户端"));
    label->setAlignment(Qt::AlignCenter);
    label->setFixedWidth(widgetWidth); //目前设标题的宽度为整个窗口的1/2
    label->setFixedHeight(70);
    label->setStyleSheet("font-size: 28px; padding: 0 10; background-color: rgb(163, 82, 255);");
    mainLayout->addWidget(label); // 加入到整体布局中

    // 每个战位对应一个groupbox，显示各个groupBox及下面的角色信息
    QHBoxLayout *cplayout = new QHBoxLayout;  //创建站位的布局对象
    checkboxGroup = new QButtonGroup();
    for(int i=0;i<configParse.getCombatPositionList().count();i++)
    {
        CheckBoxInfo checkBoxInfo;
        CombatPosition combatPosition = configParse.getCombatPositionList().at(i);
        QGroupBox *groupBox = new QGroupBox(combatPosition.estradeName);
        cplayout->addWidget(groupBox);

        // 为每个站位下创建角色
        QVBoxLayout *roleLayout = new QVBoxLayout(); // 每个站位内部的布局信息
        QList<Role> roleList = combatPosition.roleList;
        for(int j=0;j<roleList.count();j++) // 创建角色对应的复选框
        {
            Role role = roleList.at(j);
            QCheckBox *roleCheck = new QCheckBox(role.getRoleName());
            roleCheck->setFixedHeight(40);

            combatPosition.SetCurRole(role);

            connect(roleCheck, SIGNAL(clicked(bool)), this, SLOT(checkbox_click(bool)));
            roleLayout->addWidget(roleCheck);
            // 将所有复选框设置为单选
            checkboxGroup->addButton(roleCheck);
            // 存储当前复选信息
            CombatPosition *comTemp = new CombatPosition(combatPosition);
            checkBoxInfo.combatPosition = comTemp;
            checkBoxInfo.checkbox = roleCheck;
            checkInfoList.push_back(checkBoxInfo);
        }


        groupBox->setLayout(roleLayout);
    }
    mainLayout->addLayout(cplayout); // 加入到整体布局中

    // 说明信息
    descriptionedit = new QTextEdit();
    descriptionedit->setFixedHeight(70);
    descriptionedit->setEnabled(false);
    descriptionedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    mainLayout->addWidget(descriptionedit);
    // 操作按钮
    QHBoxLayout *btnlayout = new QHBoxLayout;  //创建按钮的布局对象
    okButton = new QPushButton("确定",this);
    okButton->setFixedWidth(120);
    okButton->setFixedHeight(30);
    okButton->setEnabled(false); // 默认不可被编辑
    btnlayout->addWidget(okButton);
    cancelButton = new QPushButton("退出",this);
    cancelButton->setFixedWidth(120);
    cancelButton->setFixedHeight(30);
    btnlayout->addWidget(cancelButton);
    mainLayout->addLayout(btnlayout); // 加入到整体布局中

    // 关联事件
    connect(okButton, SIGNAL(clicked()), this, SLOT(okbtn_click()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelbtn_click()));

    setLayout(mainLayout);


}

/*
 * 函数名称：UpdateWidget
 * 函数功能：当返回上一级时，根据当前的角色信息更新显示窗口
 * 参数：
 *     无
 * 返回值：
 *     无
 *
 *
 */
void RoleSelect::UpdateWidget()
{
    // 获得当前复选对应的角色对象
    for(int i=0;i<checkInfoList.count();i++)
    {
        CheckBoxInfo checkBoxInfo = checkInfoList.at(i);
        if(checkBoxInfo.combatPosition->getCurRole().getRoleName() == MainWindow::currentCombatPosition.getCurRole().getRoleName())
        {
            QString str =checkBoxInfo.checkbox->text();
            checkBoxInfo.checkbox->click();
            descriptionedit->setText(checkBoxInfo.combatPosition->getCurRole().getDescription());
            break;
        }
    }
}

/*
 *
 * 函数名称：checkbox_click
 * 函数功能：点击角色复选框响应事件，显示角色的描述信息
 * 参数：
 *      checked：如果是被选中则值为true，否则为false。
 * 返回值：
 *      无
 *
 *
 */
void RoleSelect::checkbox_click(bool checked)
{
    QString str = "";
    if(checked == true)
    {
        // 获得当前复选对应的角色对象
        for(int i=0;i<checkInfoList.count();i++)
        {
            CheckBoxInfo checkBoxInfo = checkInfoList.at(i);
            if(checkBoxInfo.checkbox->checkState() == Qt::Checked)
            {
                str = checkBoxInfo.combatPosition->getCurRole().getDescription();
                // 获取当前信息，给站位对象赋值信息
                MainWindow::currentCombatPosition = *checkBoxInfo.combatPosition;

                if(okButton->isEnabled() == false)
                     okButton->setEnabled(true);
                break;
            }
        }
    }
    descriptionedit->setText(str);
}

/*
 * 函数名称：okbtn_click
 * 函数功能：点击确定按钮，从当前窗口进入第二级窗口
 * 参数：
 *      无
 * 返回值：
 *      无
 *
 *
 *
 */
void RoleSelect::okbtn_click()
{
    // 隐藏当前的窗口
    this->hide();
    // 初始化调度窗口
    if(attemperForm == NULL)
    {
        attemperForm = new AttemperForm(this);
        attemperForm->InitWidget();
    }
    attemperForm->UpdateForm();
    attemperForm->show();
    // 进行调度切换
    QString ret = MainWindow::attmper->ChangeRole(MainWindow::currentCombatPosition);
    if(ret != "")
    {
        QMessageBox::information(this,tr("错误提示"),ret,QMessageBox::Ok);
    }
}

void RoleSelect::cancelbtn_click()
{
    exit(0);
}
