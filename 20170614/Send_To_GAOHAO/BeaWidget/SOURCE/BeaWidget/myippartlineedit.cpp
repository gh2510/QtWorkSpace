// MyIpPartLineEdit.cpp
#include "myippartlineedit.h"
#include <QIntValidator>
#include <QKeyEvent>

MyIpPartLineEdit::MyIpPartLineEdit(QWidget *parent/* = 0*/)
    : QLineEdit(parent)
{
    next_tab_ = NULL;
    this->setMaxLength(3);
    this->setFrame(false);
    this->setAlignment(Qt::AlignCenter);
    validator = new QIntValidator(0, 255, this);
    this->setValidator(validator);
    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(text_edited(const QString&)));
}

MyIpPartLineEdit::~MyIpPartLineEdit(void)
{
    if(next_tab_) delete next_tab_;
    if(validator)delete validator;
}

void MyIpPartLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    this->selectAll();
}

void MyIpPartLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Period)
    {
        if (next_tab_)
        {
            next_tab_->setFocus();
            next_tab_->selectAll();
        }
    }
    QLineEdit::keyPressEvent(event);
}

void MyIpPartLineEdit::text_edited(const QString& text)
{
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
                    if (next_tab_)
                    {
                        next_tab_->setFocus();
                        next_tab_->selectAll();
                    }
                }
            }
            else
            {
                if (next_tab_)
                {
                    next_tab_->setFocus();
                    next_tab_->selectAll();
                }
            }
        }
    }
}
