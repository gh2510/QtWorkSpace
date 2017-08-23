﻿#ifndef MYIPPARTLINEEDIT_H
#define MYIPPARTLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
class QWidget;
class QFocusEvent;
class QKeyEvent;
class MyIpPartLineEdit : public QLineEdit
{
    Q_OBJECT
    public:
        MyIpPartLineEdit(QWidget *parent = 0);
        ~MyIpPartLineEdit(void);

        void set_nexttab_edit(QLineEdit *nexttab) { next_tab_ = nexttab; }

    protected:
        virtual void focusInEvent(QFocusEvent *e);
        virtual    void keyPressEvent(QKeyEvent *event);

    private slots:
        void text_edited(const QString& text);

    private:
        QLineEdit *next_tab_;
        QValidator *validator;
};

#endif // MYIPPARTLINEEDIT_H
