#include "adderrordialog.h"
#include "ui_adderrordialog.h"
#include<QGridLayout>
AddErrorDialog::AddErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddErrorDialog)
{
        ui->setupUi(this);
        codeLabel = new QLabel("出错代码");
        infoLabel = new QLabel("出错信息");
        measureLabel=new QLabel("建议处理措施");


        codeLineEdit = new QLineEdit();
        infoLineEdit = new QTextEdit();
        measureLineEdit=new QTextEdit();


        okButton = new commonButton();
        okButton->setText("确定");
        okButton->setFixedWidth(60);
        cancelButton = new commonButton();
        cancelButton->setText("取消");
        cancelButton->setFixedWidth(60);


        gLayout = new QGridLayout;
        gLayout->setColumnStretch(1,2);
        gLayout->addWidget(codeLabel, 0, 0,Qt::AlignLeft|Qt::AlignTop);
        gLayout->addWidget(infoLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
        gLayout->addWidget(measureLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);


        gLayout->addWidget(codeLineEdit, 0, 1, Qt::AlignLeft);
        codeLabel->setBuddy (codeLineEdit);
        gLayout->addWidget(infoLineEdit,1,1,Qt::AlignLeft);
        infoLabel->setBuddy (infoLineEdit);
        gLayout->addWidget(measureLineEdit,2,1,Qt::AlignLeft);
        measureLabel->setBuddy (measureLineEdit);

        buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

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

        setWindowTitle(tr("故障管理"));
        setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);

}

AddErrorDialog::~AddErrorDialog()
{

   if(codeLabel) delete codeLabel;
   if(infoLabel) delete infoLabel;
   if( measureLabel) delete measureLabel;

   if(okButton) delete okButton;
   if(cancelButton) delete cancelButton;

   if(buttonLayout) delete buttonLayout;
   if(gLayout) delete gLayout;
  if(mainLayout) delete mainLayout;
    delete ui;

}

void AddErrorDialog::setDialogFlag(bool flag)
{
    if(flag==false)
    {
        this->codeLineEdit->setReadOnly(true);
    }
    else
    {
          this->codeLineEdit->setReadOnly(false);
    }
}

void AddErrorDialog::setDialogFlag2(bool flag)
{
    if(flag==false)
    {
        this->codeLineEdit->setReadOnly(true);
        this->infoLineEdit->setReadOnly(true);
        this->measureLineEdit->setReadOnly(true);
    }
    else
    {
          this->codeLineEdit->setReadOnly(false);
    }
}
