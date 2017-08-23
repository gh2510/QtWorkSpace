#ifndef ADDSWITCHDIALOG_H
#define ADDSWITCHDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include "myipaddredit.h"
#include "commonbutton.h"


class AddSwitchDialog:public QDialog
{
    Q_OBJECT
public:
    AddSwitchDialog(QWidget *parent = 0);
    ~AddSwitchDialog();
    void setDialogFlag(bool);
    QLineEdit * switchNameLineEdit;
    QLineEdit * descriptionLineEdit;
    MyIpAddrEdit * ipAddressLineEdit;
    MyIpAddrEdit * ipAddress2LineEdit;
    QLineEdit * locationEdit;    
    QComboBox * remarkEdit;
    void setIsEdit(bool);
private:
    QGridLayout *gLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout ;
    QLabel * nameLabel;
    QLabel * descriptionLabel;
    QLabel * addressLabel;
    QLabel * address2Label;
    QLabel * locationLabel;
    QLabel * remarkLabel;
    commonButton *okButton;
    commonButton *cancelButton;

};

#endif // ADDSWITCHDIALOG_H
