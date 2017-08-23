/********************************************************************************
** Form generated from reading UI file 'attemperpage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTEMPERPAGE_H
#define UI_ATTEMPERPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttemperPage
{
public:

    void setupUi(QWidget *AttemperPage)
    {
        if (AttemperPage->objectName().isEmpty())
            AttemperPage->setObjectName(QString::fromUtf8("AttemperPage"));
        AttemperPage->resize(400, 300);
        AttemperPage->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(AttemperPage);

        QMetaObject::connectSlotsByName(AttemperPage);
    } // setupUi

    void retranslateUi(QWidget *AttemperPage)
    {
        AttemperPage->setWindowTitle(QApplication::translate("AttemperPage", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AttemperPage: public Ui_AttemperPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTEMPERPAGE_H
