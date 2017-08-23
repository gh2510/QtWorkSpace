#include "newaddthreshdialog.h"
#include "ui_newaddthreshdialog.h"

NewAddThreshDialog::NewAddThreshDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAddThreshDialog)
{
    ui->setupUi(this);
    setTabOrder (ui->alarmNameLineEdit,ui->threshEdit);
    setTabOrder (ui->threshEdit,ui->okButton);
    setTabOrder (ui->okButton,ui->cancelButton);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("添加告警"));
//    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    setWindowFlags(Qt::Tool|Qt::WindowCloseButtonHint);
}

void NewAddThreshDialog::setNameEn(bool flag)
{
    ui->alarmNameLineEdit->setEnabled(flag);
}

QString NewAddThreshDialog::getAlarmName()
{
    return ui->alarmNameLineEdit->text();
}

QString NewAddThreshDialog::getThresh()
{
    return ui->threshEdit->text();
}

void NewAddThreshDialog::setIfEnabled(bool ifEnable)
{
    ui->alarmNameLineEdit->setEnabled(ifEnable);
}

void NewAddThreshDialog::setDialogShow(QString name, QString thresh)
{
    ui->alarmNameLineEdit->setText(name);
    ui->threshEdit->setText(thresh);
}

NewAddThreshDialog::~NewAddThreshDialog()
{
    delete ui;
}
