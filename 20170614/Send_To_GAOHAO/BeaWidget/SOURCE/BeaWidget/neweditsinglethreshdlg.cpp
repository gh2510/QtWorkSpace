#include "neweditsinglethreshdlg.h"
#include "ui_neweditsinglethreshdlg.h"

#include"connection.h"
#include<QSqlQuery>

NewEditSingleThreshDlg::NewEditSingleThreshDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEditSingleThreshDlg)
{
    ui->setupUi(this);

    QSqlQuery  query("",DBConnection::db);
    query.exec("select name from switch");
    int i=0;
    while(query.next())
    {
        ui->switchName->insertItem(i,query.value(0).toString());
        i++;
    }
    ui->switchPort->setMinimum(1);

    setTabOrder (ui->switchName,ui->switchPort);
    setTabOrder (ui->switchPort,ui->type);
    setTabOrder (ui->type,ui->value);
    setTabOrder (ui->value,ui->okButton);
    setTabOrder (ui->okButton,ui->cancelButton);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(this,SIGNAL(changePortNum(int)),ui->switchPort,SLOT(setValue(int)));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(addProtNum()));
    connect(ui->reduce,SIGNAL(clicked()),this,SLOT(reducePortBum()));

    setWindowTitle(tr("添加告警"));

    connect(ui->switchName,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(slot_indexChanged(QString)));

    //    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    setWindowFlags(Qt::Tool|Qt::WindowCloseButtonHint);
}

void NewEditSingleThreshDlg::slot_indexChanged(QString name)
{
    if(name=="H1"||name=="H2")
        ui->switchPort->setMaximum(60);
    else if(name=="A1"||name=="B1"||name=="A2"||name=="B2")
        ui->switchPort->setMaximum(52);
    else ui->switchPort->setMaximum(28);
}

void NewEditSingleThreshDlg::addProtNum()
{
    if(!ui->switchPort->isEnabled())
    {
        return;
    }
    int curPortNum = ui->switchPort->text().toInt();
    if((curPortNum+1)>ui->switchPort->maximum())
    {
        return;
    }
    else
    {
        emit changePortNum(curPortNum+1);
    }
}

void NewEditSingleThreshDlg::reducePortBum()
{
    if(!ui->switchPort->isEnabled())
    {
        return;
    }
    int curPortNum = ui->switchPort->text().toInt();
    if((curPortNum-1)<ui->switchPort->minimum())
    {
        return;
    }
    else
    {
        emit changePortNum(curPortNum-1);
    }
}

QString NewEditSingleThreshDlg::getSwitchName()
{
    return ui->switchName->currentText();
}

QString NewEditSingleThreshDlg::getSwitchPort()
{
    return ui->switchPort->text();
}

QString NewEditSingleThreshDlg::getType()
{
    return ui->type->currentText();
}

QString NewEditSingleThreshDlg::getValue()
{
    return ui->value->text();
}

void NewEditSingleThreshDlg::setDialogShow(bool ifEnabled, QString name, QString port, QString index, QString value)
{
    ui->switchName->setEnabled(ifEnabled);
    ui->switchPort->setEnabled(ifEnabled);
    ui->type->setEnabled(ifEnabled);
    ui->switchName->setCurrentIndex(ui->switchName->findText(name));
    ui->switchPort->setValue(port.toInt());
    ui->type->setCurrentIndex(ui->type->findText(index));
    ui->value->setText(value);
    ui->add->setEnabled(ifEnabled);
    ui->reduce->setEnabled(ifEnabled);
}

NewEditSingleThreshDlg::~NewEditSingleThreshDlg()
{
    delete ui;
}



