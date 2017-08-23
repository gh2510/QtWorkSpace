#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QWidget>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QMouseEvent>
#include "pushbutton_diy.h"
namespace Ui {
class AccountItem;
}

class AccountItem : public QWidget
{
    Q_OBJECT

public:
    AccountItem(QWidget *parent = 0);
    AccountItem(const QString& name,  QWidget *parent = 0);
    ~AccountItem();

    QString GetAccountNumber() const;

    void SetNickName(const QString& name);
    QString GetNickName() const;
private:
    void initView();

signals:
    void sigShowAccount(QString);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
     void enterEvent(QMouseEvent *);
     void leaveEvent(QMouseEvent *);
private:
    Ui::AccountItem *ui;
    QHBoxLayout *main_layout;
    PushButtonDIY *mButton;
    QLabel *m_lbldel;
    bool mouse_press;
};

#endif // ACCOUNTITEM_H
