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
 * �������ƣ�InitWidget
 * �������ܣ�������ݵ�ǰ�û�ѡ���վλ����ʼ������
 * ������
 *      ��
 *  ����ֵ��
 *       ��
 *
 */
void AttemperForm::InitWidget()
{
    setWindowFlags(Qt::FramelessWindowHint);
    // ���ô��ڵ�λ�ã������Ļ�ķֱ���
    int screenW = qApp->desktop()->screen()->width();
    int screenH = qApp->desktop()->screen()->height();
    float hlvt = 0.9f;
    this->setGeometry(0, 0 ,screenW, screenH * (1.0f-hlvt)); // screenH * hlvt
    CombatPosition combatPosition = MainWindow::currentCombatPosition;
    // ѡ�񲼾�ģʽ
    QHBoxLayout *layout = new QHBoxLayout;  //������ť�Ĳ��ֶ���
    // ����վλ

    int textWidth = 120; // һ��ؼ��Ŀ��

    QLabel *cpLabelSign = new QLabel("��ǰսλ��");
    cpLabelSign->setAlignment(Qt::AlignCenter);
    cpLabelSign->setFixedWidth(textWidth);
    layout->addWidget(cpLabelSign);
    cpLabel = new QLabel(combatPosition.estradeName);
    cpLabel->setFixedWidth(textWidth);
    cpLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(cpLabel);

    // ������ɫ
    QLabel *rlLabelSign = new QLabel("��ǰ��ɫ��");
    rlLabelSign->setAlignment(Qt::AlignCenter);
    rlLabelSign->setFixedWidth(textWidth);
    layout->addWidget(rlLabelSign);
    // ����������
    rlCombox = new QComboBox();
    for(int i=0;i<combatPosition.roleList.count();i++)
    {
        rlCombox->addItem(combatPosition.roleList.at(i).getRoleName());
    }
    connect(rlCombox,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(indexChanged(const QString&)));
    layout->addWidget(rlCombox);
    rlCombox->setFixedWidth(textWidth);
    // ���һ�����ɿؼ�
    layout->addStretch(3);
    // ���һ�鰴ť
    retBtn = new QPushButton();
    retBtn->setText("����");
    retBtn->setFixedWidth(90);
    layout->addWidget(retBtn);
    exitBtn = new QPushButton();
    exitBtn->setText("�˳�");
    exitBtn->setFixedWidth(90);
    layout->addWidget(exitBtn);

    setLayout(layout);

    // �����¼�
    connect(retBtn, SIGNAL(clicked()), this, SLOT(resbtn_click()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitbtn_click()));

}

/*
 * �������ƣ�UpdateForm
 * �������ܣ�����վλ����ɫ����Ϣ
 * ������
 *     ��
 * ����ֵ��
 *      ��
 *
 */
void AttemperForm::UpdateForm()
{
    CombatPosition combatPosition;
    combatPosition = MainWindow::currentCombatPosition;
    // ����վλ����
    cpLabel->setText(combatPosition.estradeName);
    // ���½�ɫ�������б�
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
    // ���ص���һ������
    this->hide();
    // ��յ�ǰѡ�����Ϣ
    ((RoleSelect*)frontWidget)->UpdateWidget();
    frontWidget->show();
}

void AttemperForm::exitbtn_click()
{
    exit(0);
}

/*
 *
 * �������ƣ�indexChanged
 * �������ܣ���ɫ��combo�л���Ӧ�¼�
 * ������
 *     text���л�������
 * ����ֵ��
 *     ��
 *
 */
void AttemperForm::indexChanged(const QString& text)
{
    // ���������жϵ�ǰ��ɫ����
    if(text == "") // ��ʾ��ղ������¼�
        return;
    Role role;

    for(int i=0;i<MainWindow::currentCombatPosition.roleList.count();i++)
    {
        role = MainWindow::currentCombatPosition.roleList.at(i);
        if(role.getRoleName() == text)
        {
            MainWindow::currentCombatPosition.SetCurRole(role);
            QString ret = MainWindow::attmper->ChangeRole(MainWindow::currentCombatPosition); // ���е�������
            if(ret != "")
            {
                MainWindow::WarnMessage(ret);
            }
            return;
        }
    }
}

