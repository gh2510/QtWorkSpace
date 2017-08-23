#include "addthreshdialog.h"


AddThreshDialog::AddThreshDialog(QWidget* parent)
    :QDialog(parent)
{

    alarmnameLabel = new QLabel("性能参数");
    threshLabel=new QLabel("阈值设置");
    alarmNameLineEdit = new QLineEdit(this);
    threshEdit= new QLineEdit(this);
    okButton = new QPushButton("确定",this);
    cancelButton = new QPushButton("取消",this);


    setTabOrder (alarmNameLineEdit,threshEdit);
    setTabOrder (threshEdit,okButton);
    setTabOrder (okButton,cancelButton);

    gLayout = new QGridLayout;
    gLayout->setColumnStretch(1,3);
    gLayout->addWidget(alarmnameLabel, 0, 0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(alarmNameLineEdit, 0, 1,1,3,Qt::AlignLeft|Qt::AlignTop);
    alarmNameLineEdit->setFixedWidth(200);   //控件固定长度显示
    alarmnameLabel->setBuddy (alarmNameLineEdit);

    gLayout->addWidget(threshLabel,2,0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(threshEdit,2,1,Qt::AlignLeft);
    threshEdit->setFixedWidth(200);   //控件固定长度显示
   threshLabel->setBuddy (threshEdit);

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
}

AddThreshDialog::~AddThreshDialog()
{

    if(cancelButton)delete cancelButton;
    if(okButton)delete okButton;
    if(alarmnameLabel) delete alarmnameLabel;
    if(threshLabel)delete threshLabel;
    if(alarmNameLineEdit)delete alarmNameLineEdit;
    if(threshEdit)delete threshEdit;

    if(buttonLayout)delete buttonLayout;
    if(gLayout)delete gLayout;
     if(mainLayout) delete mainLayout;

}

 void AddThreshDialog::setNameEn(bool flag)
 {
     alarmNameLineEdit->setEnabled(flag);
 }
