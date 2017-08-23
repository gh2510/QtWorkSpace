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
 * �������ƣ�InitWidget
 * �������ܣ�����սλ��Ϣ����̬���ɽ��棬����վλ�ͽ�ɫ
 * ������
 *     combatPosition��վλ��Ϣ��
 * ����ֵ��
 *     �ޡ�
 *
 *
 */
void RoleSelect::InitWidget(ConfigParse &configParse)
{
    setWindowFlags(Qt::FramelessWindowHint);
    // ���ݵ�ǰ����ϵͳսλ���������Լ�����ɫ����������̬���ɴ��ڿ�Ⱥ͸߶�
    int combatPositionNum = configParse.getCombatPositionNum();
    int maxRoleNum = configParse.getMaxRoleNum();

    if(combatPositionNum == 0)
    {
        QMessageBox::information(this,tr("������ʾ"),tr("�����ļ���δ���սλ��Ϣ�����ʵ��"),QMessageBox::Ok);
        exit(0); // ֱ���˳��ĳ���
    }
    if(maxRoleNum == 0)
    {
       QMessageBox::information(this,tr("������ʾ"),tr("�����ļ���δ��ý�ɫ��Ϣ�����ʵ��"),QMessageBox::Ok);
        exit(0); // ֱ���˳��ĳ���
    }

    // ���ɿ�Ⱥ͸߶ȣ�Ŀǰ�ݶ�ÿ��վλռ�еĿ��Ϊ 50�����ο��Ԥ��Ϊ 60���߶�ÿ����ɫռ��20�����Ϊ10������߶�Ϊ0�����¿ռ�Ϊ10
    int widgetWidth = 60*2 + combatPositionNum * 120;
    int widgetHeight = 50*2 + maxRoleNum * 40 + (maxRoleNum-1) * 30 + 40;

    setFixedSize(widgetWidth,widgetHeight);

    // �����������ڵ�layout�����ڷ�Ϊ�����֣�����������ɫѡ�����Լ��˳���ť
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // ��ʾ������
    QLabel *label = new QLabel(tr("���񻯵���ϵͳ�ͻ���"));
    label->setAlignment(Qt::AlignCenter);
    label->setFixedWidth(widgetWidth); //Ŀǰ�����Ŀ��Ϊ�������ڵ�1/2
    label->setFixedHeight(70);
    label->setStyleSheet("font-size: 28px; padding: 0 10; background-color: rgb(163, 82, 255);");
    mainLayout->addWidget(label); // ���뵽���岼����

    // ÿ��սλ��Ӧһ��groupbox����ʾ����groupBox������Ľ�ɫ��Ϣ
    QHBoxLayout *cplayout = new QHBoxLayout;  //����վλ�Ĳ��ֶ���
    checkboxGroup = new QButtonGroup();
    for(int i=0;i<configParse.getCombatPositionList().count();i++)
    {
        CheckBoxInfo checkBoxInfo;
        CombatPosition combatPosition = configParse.getCombatPositionList().at(i);
        QGroupBox *groupBox = new QGroupBox(combatPosition.estradeName);
        cplayout->addWidget(groupBox);

        // Ϊÿ��վλ�´�����ɫ
        QVBoxLayout *roleLayout = new QVBoxLayout(); // ÿ��վλ�ڲ��Ĳ�����Ϣ
        QList<Role> roleList = combatPosition.roleList;
        for(int j=0;j<roleList.count();j++) // ������ɫ��Ӧ�ĸ�ѡ��
        {
            Role role = roleList.at(j);
            QCheckBox *roleCheck = new QCheckBox(role.getRoleName());
            roleCheck->setFixedHeight(40);

            combatPosition.SetCurRole(role);

            connect(roleCheck, SIGNAL(clicked(bool)), this, SLOT(checkbox_click(bool)));
            roleLayout->addWidget(roleCheck);
            // �����и�ѡ������Ϊ��ѡ
            checkboxGroup->addButton(roleCheck);
            // �洢��ǰ��ѡ��Ϣ
            CombatPosition *comTemp = new CombatPosition(combatPosition);
            checkBoxInfo.combatPosition = comTemp;
            checkBoxInfo.checkbox = roleCheck;
            checkInfoList.push_back(checkBoxInfo);
        }


        groupBox->setLayout(roleLayout);
    }
    mainLayout->addLayout(cplayout); // ���뵽���岼����

    // ˵����Ϣ
    descriptionedit = new QTextEdit();
    descriptionedit->setFixedHeight(70);
    descriptionedit->setEnabled(false);
    descriptionedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    mainLayout->addWidget(descriptionedit);
    // ������ť
    QHBoxLayout *btnlayout = new QHBoxLayout;  //������ť�Ĳ��ֶ���
    okButton = new QPushButton("ȷ��",this);
    okButton->setFixedWidth(120);
    okButton->setFixedHeight(30);
    okButton->setEnabled(false); // Ĭ�ϲ��ɱ��༭
    btnlayout->addWidget(okButton);
    cancelButton = new QPushButton("�˳�",this);
    cancelButton->setFixedWidth(120);
    cancelButton->setFixedHeight(30);
    btnlayout->addWidget(cancelButton);
    mainLayout->addLayout(btnlayout); // ���뵽���岼����

    // �����¼�
    connect(okButton, SIGNAL(clicked()), this, SLOT(okbtn_click()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelbtn_click()));

    setLayout(mainLayout);


}

/*
 * �������ƣ�UpdateWidget
 * �������ܣ���������һ��ʱ�����ݵ�ǰ�Ľ�ɫ��Ϣ������ʾ����
 * ������
 *     ��
 * ����ֵ��
 *     ��
 *
 *
 */
void RoleSelect::UpdateWidget()
{
    // ��õ�ǰ��ѡ��Ӧ�Ľ�ɫ����
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
 * �������ƣ�checkbox_click
 * �������ܣ������ɫ��ѡ����Ӧ�¼�����ʾ��ɫ��������Ϣ
 * ������
 *      checked������Ǳ�ѡ����ֵΪtrue������Ϊfalse��
 * ����ֵ��
 *      ��
 *
 *
 */
void RoleSelect::checkbox_click(bool checked)
{
    QString str = "";
    if(checked == true)
    {
        // ��õ�ǰ��ѡ��Ӧ�Ľ�ɫ����
        for(int i=0;i<checkInfoList.count();i++)
        {
            CheckBoxInfo checkBoxInfo = checkInfoList.at(i);
            if(checkBoxInfo.checkbox->checkState() == Qt::Checked)
            {
                str = checkBoxInfo.combatPosition->getCurRole().getDescription();
                // ��ȡ��ǰ��Ϣ����վλ����ֵ��Ϣ
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
 * �������ƣ�okbtn_click
 * �������ܣ����ȷ����ť���ӵ�ǰ���ڽ���ڶ�������
 * ������
 *      ��
 * ����ֵ��
 *      ��
 *
 *
 *
 */
void RoleSelect::okbtn_click()
{
    // ���ص�ǰ�Ĵ���
    this->hide();
    // ��ʼ�����ȴ���
    if(attemperForm == NULL)
    {
        attemperForm = new AttemperForm(this);
        attemperForm->InitWidget();
    }
    attemperForm->UpdateForm();
    attemperForm->show();
    // ���е����л�
    QString ret = MainWindow::attmper->ChangeRole(MainWindow::currentCombatPosition);
    if(ret != "")
    {
        QMessageBox::information(this,tr("������ʾ"),ret,QMessageBox::Ok);
    }
}

void RoleSelect::cancelbtn_click()
{
    exit(0);
}
