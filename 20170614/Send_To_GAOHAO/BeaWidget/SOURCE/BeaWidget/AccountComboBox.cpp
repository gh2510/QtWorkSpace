#include "AccountComboBox.h"
#include "accountitem.h"
#include <QFile>
AccountComboBox::AccountComboBox(QWidget *parent)
    : QComboBox(parent)
{
    setEditable(true);
    setFixedSize(220,30);

    QFile qss(":/QSS/QSS/combox.qss");
    qss.open(QIODevice::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();

    mpListWidget = new QListWidget();
    setModel(mpListWidget->model());
    setView(mpListWidget);
}

AccountComboBox::~AccountComboBox()
{
    if(mpListWidget)
        delete mpListWidget;
}

void AccountComboBox::AddAccount( AccountItem* pAccountItem )
{
    connect(pAccountItem, SIGNAL(sigShowAccount(QString)), this, SLOT(OnShowAccount(QString)));


    QListWidgetItem* item = new QListWidgetItem(mpListWidget);
    mpListWidget->setItemWidget(item, pAccountItem);
}

void AccountComboBox::OnShowAccount(QString account)
{
    setEditText(account);
    hidePopup();
}



