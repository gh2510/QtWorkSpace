#include "newadduserdialog.h"
#include "ui_newadduserdialog.h"

NewAddUserDialog::NewAddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAddUserDialog)
{
    ui->setupUi(this);

    setTabOrder (ui->userNameLineEdit,ui->passwordLineEdit);
    setTabOrder (ui->passwordLineEdit,ui->userlevelEdit);
    setTabOrder (ui->userlevelEdit,ui->okButton);
    setTabOrder (ui->okButton,ui->cancelButton);

    ui->nameLabel->setBuddy(ui->userNameLineEdit);
    ui->passwordLabel->setBuddy(ui->passwordLineEdit);
    ui->userlevelLabel->setBuddy(ui->userlevelEdit);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("添加用户"));
//    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    setWindowFlags(Qt::Tool|Qt::WindowCloseButtonHint);

}

void NewAddUserDialog::setNameEn(bool flag)
{
    ui->userNameLineEdit->setEnabled(flag);
}

void NewAddUserDialog::setInfoShow(QString name, QString password, QString level)
{
    ui->userNameLineEdit->setText(name);
    ui->passwordLineEdit->setText(password);
    ui->userlevelEdit->setCurrentIndex(ui->userlevelEdit->findText(level));
}

QString NewAddUserDialog::getUserName() const
{
    return ui->userNameLineEdit->text();
}

QString NewAddUserDialog::getPassword() const
{
    return ui->passwordLineEdit->text();
}

QString NewAddUserDialog::getUserLevel() const
{
    return ui->userlevelEdit->currentText();
}

NewAddUserDialog::~NewAddUserDialog()
{
    delete ui;
}
