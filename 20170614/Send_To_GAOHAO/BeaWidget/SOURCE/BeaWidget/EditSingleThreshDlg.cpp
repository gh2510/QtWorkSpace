#include<QSqlQuery>
#include"connection.h"
#include "EditSingleThreshDlg.h"


EditSingleThreshDlg::EditSingleThreshDlg(QWidget* parent)
    :QDialog(parent)
{

    switchnameLabel = new QLabel("交换机名称");
    switchportLabel=new QLabel("端口");
    typeLabel=new QLabel("类型");
    valueLabel=new QLabel("阈值");

    QSqlQuery  query("",DBConnection::db);
    switchName= new QComboBox(this);
    query.exec("select name from switch");
    int i=0;
    while(query.next())
    {
        switchName->insertItem(i,query.value(0).toString());
        i++;
    }
    switchPort = new QSpinBox(this);
    switchPort->setMinimum(1);
    type = new QComboBox(this);
    type->insertItem(0,"进速率");
    type->insertItem(1,"出速率");
    value = new QLineEdit(this);
    okButton = new QPushButton("确定",this);
    cancelButton = new QPushButton("取消",this);


    setTabOrder (switchName,switchPort);
    setTabOrder (switchPort,type);
    setTabOrder (type,value);
    setTabOrder (value,okButton);
    setTabOrder (okButton,cancelButton);

    gLayout = new QGridLayout;
    gLayout->setColumnStretch(1,2);
    gLayout->addWidget(switchnameLabel, 0, 0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(switchName, 0, 1,Qt::AlignLeft|Qt::AlignTop);
    switchnameLabel->setBuddy (switchName);

    gLayout->addWidget(switchportLabel, 1, 0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(switchPort, 1, 1,Qt::AlignLeft|Qt::AlignTop);
    switchportLabel->setBuddy (switchPort);

    gLayout->addWidget(typeLabel, 2, 0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(type, 2, 1,Qt::AlignLeft|Qt::AlignTop);
    typeLabel->setBuddy (type);

    gLayout->addWidget(valueLabel,3,0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(value,3,1,Qt::AlignRight);
    valueLabel->setBuddy (value);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch ();
    buttonLayout->addWidget(okButton);
    buttonLayout->addStretch ();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch ();

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    mainLayout->addLayout (buttonLayout);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(20);
    setLayout(mainLayout);
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(54,54,54));
    palette.setColor(QPalette::WindowText,QColor("white"));
    setPalette(palette);

    setWindowTitle(tr("添加告警"));
    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    connect(switchName,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_indexChanged(QString)));
}

EditSingleThreshDlg::~EditSingleThreshDlg()
{

    if(cancelButton)delete cancelButton;
    if(okButton)delete okButton;
    if(switchName) delete switchName;
    if(type) delete type;
    if(value) delete value;
    if(switchPort) delete switchPort;
    if(switchnameLabel) delete switchnameLabel;
    if(switchportLabel) delete switchportLabel;
    if(typeLabel) delete typeLabel;
    if(valueLabel) delete valueLabel;

    if(buttonLayout)delete buttonLayout;
    if(gLayout)delete gLayout;
    if(mainLayout) delete mainLayout;

}

void EditSingleThreshDlg::slot_indexChanged(QString name)
{
    if(name=="H1"||name=="H2")
        switchPort->setMaximum(60);
    else if(name=="A1"||name=="B1"||name=="A2"||name=="B2")
        switchPort->setMaximum(52);
    else switchPort->setMaximum(28);
}
