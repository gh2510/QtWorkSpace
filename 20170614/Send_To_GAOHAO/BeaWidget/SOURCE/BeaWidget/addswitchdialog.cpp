#include "addswitchdialog.h"



AddSwitchDialog::AddSwitchDialog(QWidget* parent)
    :QDialog(parent)
{
    nameLabel = new QLabel("交换机标识");
    descriptionLabel = new QLabel("交换机名称");
    addressLabel = new QLabel("带内IP地址");
    address2Label = new QLabel("带外IP地址");
    locationLabel=new QLabel("位置");
    remarkLabel=new QLabel("端口数量");

    switchNameLineEdit = new QLineEdit();
    descriptionLineEdit = new QLineEdit();

    ipAddress2LineEdit = new MyIpAddrEdit(this);
    ipAddressLineEdit = new MyIpAddrEdit(this);


    ipAddressLineEdit->setText ("0.0.0.0");
    ipAddressLineEdit->setPosition (100,11);
    ipAddressLineEdit->show ();


    ipAddress2LineEdit->setText ("0.0.0.0");
    ipAddress2LineEdit->setPosition (100,43);
    ipAddress2LineEdit->show ();

    locationEdit=new QLineEdit();
    remarkEdit=new QComboBox();
    remarkEdit->insertItem(0,"28");
    remarkEdit->insertItem(1,"52");
    remarkEdit->insertItem(2,"60");

    okButton = new commonButton();
    okButton->setText("确定");
    okButton->setFixedWidth(60);
    cancelButton = new commonButton();
    cancelButton->setText("取消");
    cancelButton->setFixedWidth(60);

    setTabOrder (ipAddressLineEdit,ipAddress2LineEdit);
    setTabOrder (ipAddress2LineEdit,switchNameLineEdit);
    setTabOrder (switchNameLineEdit,descriptionLineEdit);
    setTabOrder (descriptionLineEdit,locationEdit);
    setTabOrder (locationEdit,remarkEdit);
    setTabOrder (remarkEdit,okButton);
    setTabOrder (okButton,cancelButton);

    gLayout = new QGridLayout;
    gLayout->setColumnStretch(1,2);
    gLayout->addWidget(addressLabel, 0, 0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(address2Label, 1, 0,Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(nameLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(descriptionLabel, 3, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(locationLabel, 4, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(remarkLabel, 5, 0, Qt::AlignLeft|Qt::AlignTop);

    gLayout->addWidget(switchNameLineEdit, 2, 1, Qt::AlignRight);
    nameLabel->setBuddy (switchNameLineEdit);    
    gLayout->addWidget(descriptionLineEdit,3,1,Qt::AlignRight);
    descriptionLabel->setBuddy (descriptionLineEdit);
    gLayout->addWidget(locationEdit,4,1,Qt::AlignRight);
    locationLabel->setBuddy (locationEdit);
    gLayout->addWidget(remarkEdit,5,1,Qt::AlignRight);
    remarkLabel->setBuddy (remarkEdit);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 6, 1, Qt::AlignRight);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(20);
    setLayout(mainLayout);
    connect(okButton, SIGNAL(click()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(click()), this, SLOT(reject()));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(54,54,54));
    palette.setColor(QPalette::WindowText,QColor("white"));
    setPalette(palette);

    setWindowTitle(tr("添加交换机"));
   setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
}

AddSwitchDialog::~AddSwitchDialog()
{
    if(cancelButton)delete cancelButton;
    if(okButton)delete okButton;
    if(remarkEdit)delete remarkEdit;
    if(locationEdit)delete locationEdit;

    if(ipAddressLineEdit)delete ipAddressLineEdit;

    if(switchNameLineEdit)delete switchNameLineEdit;
    if(nameLabel) delete nameLabel;
    if(addressLabel)delete addressLabel;
    if(locationLabel)delete locationLabel;
    if(remarkLabel)delete remarkLabel;

    if(buttonLayout)delete buttonLayout;
    if(gLayout)delete gLayout;
    if(mainLayout) delete mainLayout;


}
void AddSwitchDialog::setIsEdit(bool flag)
{
    switchNameLineEdit->setReadOnly(flag);
}
void AddSwitchDialog::setDialogFlag(bool flag)
{
    if(flag==false)
    {
        this->switchNameLineEdit->setReadOnly(true);
    }
    else
    {
          this->switchNameLineEdit->setReadOnly(false);
    }
}
