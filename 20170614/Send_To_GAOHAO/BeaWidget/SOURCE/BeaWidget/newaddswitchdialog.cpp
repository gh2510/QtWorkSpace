#include "newaddswitchdialog.h"
#include "ui_newaddswitchdialog.h"

NewAddSwitchDialog::NewAddSwitchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAddSwitchDialog)
{
    ui->setupUi(this);
    ipLineEdits<<ui->ip_part1_In<<ui->ip_part2_In<<ui->ip_part3_In<<ui->ip_part4_In
                 <<ui->ip_part1_Out<<ui->ip_part2_Out<<ui->ip_part3_Out<<ui->ip_part4_Out;

    this->setText ("0.0.0.0",0);
    this->setText ("0.0.0.0",1);

    this->iniTabOrder();

    ui->nameLabel->setBuddy(ui->switchNameLineEdit);
    ui->descriptionLabel->setBuddy(ui->descriptionLineEdit);
    ui->locationLabel->setBuddy(ui->locationEdit);
    ui->remarkLabel->setBuddy(ui->remarkEdit);

    for(int i=0;i<ipLineEdits.count();i++)
    {
        connect(ipLineEdits.at(i), SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
        connect(ipLineEdits.at(i), SIGNAL(textEdited(const QString&)), this, SLOT(texteditedslot(const QString&)));
    }

    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));

    setWindowTitle(tr("添加告警"));
//    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    setWindowFlags(Qt::Tool|Qt::WindowCloseButtonHint);

//    Qt::WindowFlags flags=Qt::Dialog;
//    flags |=Qt::WindowMinMaxButtonsHint;
//    flags |=Qt::WindowCloseButtonHint;
//    setWindowFlags(Qt::WindowCloseButtonHint);
}

void NewAddSwitchDialog::iniTabOrder()
{
    setTabOrder(ui->ip_part1_In,ui->ip_part2_In);
    setTabOrder(ui->ip_part2_In,ui->ip_part3_In);
    setTabOrder(ui->ip_part3_In,ui->ip_part4_In);
    setTabOrder(ui->ip_part4_In,ui->ip_part1_Out);
    setTabOrder(ui->ip_part1_Out,ui->ip_part2_Out);
    setTabOrder(ui->ip_part2_Out,ui->ip_part3_Out);
    setTabOrder(ui->ip_part3_Out,ui->ip_part4_Out);
    setTabOrder (ui->ip_part4_Out,ui->switchNameLineEdit);
    setTabOrder (ui->switchNameLineEdit,ui->descriptionLineEdit);
    setTabOrder (ui->descriptionLineEdit,ui->locationEdit);
    setTabOrder (ui->locationEdit,ui->remarkEdit);
    setTabOrder (ui->remarkEdit,ui->okButton);
    setTabOrder (ui->okButton,ui->cancelButton);
}

void NewAddSwitchDialog::setDialogFlag(bool flag)
{
    if(flag==false)
    {
        ui->switchNameLineEdit->setReadOnly(true);
    }
    else
    {
          ui->switchNameLineEdit->setReadOnly(false);
    }
}

void NewAddSwitchDialog::setIsEdit(bool flag)
{
    ui->switchNameLineEdit->setReadOnly(flag);
}

void NewAddSwitchDialog::textchangedslot(const QString& /*text*/)
{
    QString ippart1, ippart2, ippart3, ippart4;
    QLineEdit *edit = qobject_cast<QLineEdit*>(QObject::sender());
    if(ipLineEdits.count()<0)
    {
        return;
    }
    if(ipLineEdits.indexOf(edit)<4)
    {
        ippart1 = ui->ip_part1_In->text();
        ippart2 = ui->ip_part2_In->text();
        ippart3 = ui->ip_part3_In->text();
        ippart4 = ui->ip_part4_In->text();
    }
    else
    {
        ippart1 = ui->ip_part1_Out->text();
        ippart2 = ui->ip_part2_Out->text();
        ippart3 = ui->ip_part3_Out->text();
        ippart4 = ui->ip_part4_Out->text();
    }


    QString ipaddr = QString("%1.%2.%3.%4")
                     .arg(ippart1)
                     .arg(ippart2)
                     .arg(ippart3)
                     .arg(ippart4);

    emit textchanged(ipaddr);
}

void NewAddSwitchDialog::texteditedslot(const QString &text)
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(QObject::sender());
    int index = ipLineEdits.indexOf(edit);
    QIntValidator v(0, 255, this);
    QString ipaddr = text;
    int pos = 0;
    QValidator::State state = v.validate(ipaddr, pos);
    if (state == QValidator::Acceptable)
    {
        if (ipaddr.size() > 1)
        {
            if (ipaddr.size() == 2)
            {
                int ipnum = ipaddr.toInt();

                if (ipnum > 25)
                {
                    if (index!=3&&index!=7)
                    {
                        ipLineEdits.at(index+1)->setFocus();
                        ipLineEdits.at(index+1)->selectAll();
                    }
                }
            }
            else
            {
                if (index!=3&&index!=7)
                {
                    ipLineEdits.at(index+1)->setFocus();
                    ipLineEdits.at(index+1)->selectAll();
                }
            }
        }
    }
    QString ippart1, ippart2, ippart3, ippart4;
    if(ipLineEdits.count()<0)
    {
        return;
    }
    if(ipLineEdits.indexOf(edit)<4)
    {
        ippart1 = ui->ip_part1_In->text();
        ippart2 = ui->ip_part2_In->text();
        ippart3 = ui->ip_part3_In->text();
        ippart4 = ui->ip_part4_In->text();
    }
    else
    {
        ippart1 = ui->ip_part1_Out->text();
        ippart2 = ui->ip_part2_Out->text();
        ippart3 = ui->ip_part3_Out->text();
        ippart4 = ui->ip_part4_Out->text();
    }

    QString ip = QString("%1.%2.%3.%4")
        .arg(ippart1)
        .arg(ippart2)
        .arg(ippart3)
        .arg(ippart4);

    emit textedited(ip);
}

void NewAddSwitchDialog::setReadOnly (bool readonly)
{
    if(ipLineEdits.count()>0)
    {
        for(int i=0;i<ipLineEdits.count();i++)
        {
            ipLineEdits.at(i)->setReadOnly(readonly);
        }
    }
}

void NewAddSwitchDialog::setText(const QString &text, const int index)
{
    QString ippart1, ippart2, ippart3, ippart4;
    QString qstring_validate = text;

    // IP地址验证
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator regexp_validator(regexp, this);
    int nPos = 0;
    QValidator::State state = regexp_validator.validate(qstring_validate, nPos);
    // IP合法
    if (state == QValidator::Acceptable)
    {
        QStringList ippartlist = text.split(".");

        int strcount = ippartlist.size();
        int index = 0;
        if (index < strcount)
        {
            ippart1 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart2 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart3 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart4 = ippartlist.at(index);
        }
    }
    switch (index)
    {
    case 0:
        ui->ip_part1_In->setText(ippart1);
        ui->ip_part2_In->setText(ippart2);
        ui->ip_part3_In->setText(ippart3);
        ui->ip_part4_In->setText(ippart4);
        break;
    case 1:
        ui->ip_part1_Out->setText(ippart1);
        ui->ip_part2_Out->setText(ippart2);
        ui->ip_part3_Out->setText(ippart3);
        ui->ip_part4_Out->setText(ippart4);
        break;
    }
}

void NewAddSwitchDialog::setInfShow(QString name, QString address, QString address2, QString description, QString location, QString remark)
{
    ui->switchNameLineEdit->setText(name);
    this->setText(address,0);
    this->setText(address2,1);
    ui->descriptionLineEdit->setText(description);
    ui->locationEdit->setText(location);
    ui->remarkEdit->setCurrentIndex(ui->remarkEdit->findText(remark));
}

QString NewAddSwitchDialog::getIP_In()
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ui->ip_part1_In->text();
    ippart2 = ui->ip_part2_In->text();
    ippart3 = ui->ip_part3_In->text();
    ippart4 = ui->ip_part4_In->text();

    return QString("%1.%2.%3.%4")
        .arg(ippart1)
        .arg(ippart2)
        .arg(ippart3)
        .arg(ippart4);
}

QString NewAddSwitchDialog::getIp_Out()
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ui->ip_part1_Out->text();
    ippart2 = ui->ip_part2_Out->text();
    ippart3 = ui->ip_part3_Out->text();
    ippart4 = ui->ip_part4_Out->text();

    return QString("%1.%2.%3.%4")
        .arg(ippart1)
        .arg(ippart2)
        .arg(ippart3)
        .arg(ippart4);
}

QString NewAddSwitchDialog::getName()
{
    return ui->switchNameLineEdit->text();
}

QString NewAddSwitchDialog::getDescription()
{
    return ui->descriptionLineEdit->text();
}

QString NewAddSwitchDialog::getLocation()
{
    return ui->locationEdit->text();
}

QString NewAddSwitchDialog::getRemark()
{
    return ui->remarkEdit->currentText();
}

NewAddSwitchDialog::~NewAddSwitchDialog()
{
    delete ui;
}
