#ifndef ACCOUNTCOMBOBOX_H
#define ACCOUNTCOMBOBOX_H



#include <QComboBox>
#include <QListWidget>

class AccountItem;

class AccountComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit AccountComboBox(QWidget *parent=0);
    ~AccountComboBox();

    void AddAccount(AccountItem* pAccountItem);


private slots:
    void OnShowAccount(QString account);


private:
    QListWidget* mpListWidget;
};



#endif // ACCOUNTCOMBOBOX_H
