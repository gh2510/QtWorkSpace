#include "newadderrordialog.h"
#include "ui_newadderrordialog.h"

NewAddErrorDialog::NewAddErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAddErrorDialog)
{
    ui->setupUi(this);

    ui->codeLabel->setBuddy (ui->codeLineEdit);
    ui->infoLabel->setBuddy (ui->infoLineEdit);
    ui->measureLabel->setBuddy (ui->measureLineEdit);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("故障管理"));
//    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    setWindowFlags(Qt::Tool|Qt::WindowCloseButtonHint);
}

void NewAddErrorDialog::setDialogFlag(bool flag)
{
    if(flag==false)
    {
        ui->codeLineEdit->setReadOnly(true);
    }
    else
    {
        ui->codeLineEdit->setReadOnly(false);
    }
}

void NewAddErrorDialog::setDialogFlag2(bool flag)
{
    if(flag==false)
    {
        ui->codeLineEdit->setReadOnly(true);
        ui->infoLineEdit->setReadOnly(true);
        ui->measureLineEdit->setReadOnly(true);
    }
    else
    {
        ui->codeLineEdit->setReadOnly(false);
    }
}

void NewAddErrorDialog::setText(QString errorcode, QString errorinfo, QString measure)
{
    ui->codeLineEdit->setText(errorcode);
    ui->infoLineEdit->setText(errorinfo);
    ui->measureLineEdit->setText(measure);
}

QString NewAddErrorDialog::getCode()
{
    return ui->codeLineEdit->text();
}

QString NewAddErrorDialog::getInfo()
{
    return ui->infoLineEdit->toPlainText();
}

QString NewAddErrorDialog::getMeasure()
{
    return ui->measureLineEdit->toPlainText();
}

NewAddErrorDialog::~NewAddErrorDialog()
{
    delete ui;
}

