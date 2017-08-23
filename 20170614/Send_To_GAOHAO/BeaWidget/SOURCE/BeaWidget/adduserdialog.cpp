#include "adduserdialog.h"
#include<QDebug>


AddUserDialog::AddUserDialog(QWidget* parent)
    :QDialog(parent)
{
    nameLabel = new QLabel("用户名");
    passwordLabel = new QLabel("密码");
    userlevelLabel=new QLabel("用户级别");
    userNameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    userlevelEdit= new QComboBox(this);
    userlevelEdit->addItem ("普通用户");
    userlevelEdit->addItem ("管理员");

    okButton = new QPushButton("确定",this);
    cancelButton = new QPushButton("取消",this);

    setTabOrder (userNameLineEdit,passwordLineEdit);
    setTabOrder (passwordLineEdit,userlevelEdit);
    setTabOrder (userlevelEdit,okButton);
    setTabOrder (okButton,cancelButton);

    gLayout = new QGridLayout;
    gLayout->setColumnStretch(1,2);
    gLayout->addWidget(nameLabel, 0, 0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(userNameLineEdit, 0, 1,Qt::AlignLeft|Qt::AlignTop);
    nameLabel->setBuddy (userNameLineEdit);

    gLayout->addWidget(passwordLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(passwordLineEdit, 1, 1, Qt::AlignRight);
    passwordLabel->setBuddy (passwordLineEdit);

    gLayout->addWidget(userlevelLabel,2,0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(userlevelEdit,2,1,Qt::AlignRight);
    userlevelLabel->setBuddy (userlevelEdit);

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

    setWindowTitle(tr("添加用户"));
    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
}

AddUserDialog::~AddUserDialog()
{

    if(cancelButton)delete cancelButton;
    if(okButton)delete okButton;
    if(nameLabel)delete nameLabel;
    if(passwordLabel)delete passwordLabel;
    if(userlevelLabel)delete userlevelLabel;
    if(userNameLineEdit)delete userNameLineEdit;
    if(passwordLineEdit)delete passwordLineEdit;
    if(userlevelEdit)delete userlevelEdit;
    if(buttonLayout)delete buttonLayout;
    if(gLayout)delete gLayout;
     if(mainLayout) delete mainLayout;

}

void AddUserDialog::setNameEn(bool flag)
{
    userNameLineEdit->setEnabled(flag);
}
