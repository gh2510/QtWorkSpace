/********************************************************************************
** Form generated from reading UI file 'attemperform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTEMPERFORM_H
#define UI_ATTEMPERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttemperForm
{
public:

    void setupUi(QWidget *AttemperForm)
    {
        if (AttemperForm->objectName().isEmpty())
            AttemperForm->setObjectName(QString::fromUtf8("AttemperForm"));
        AttemperForm->resize(400, 300);
        AttemperForm->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	\n"
"	\n"
"	background-color: rgb(234, 196, 255);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	\n"
"	font: 16pt \"\346\245\267\344\275\223\";\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"	font: 16pt \"\346\245\267\344\275\223\";\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	font: 16pt \"\346\245\267\344\275\223\";\n"
"}"));

        retranslateUi(AttemperForm);

        QMetaObject::connectSlotsByName(AttemperForm);
    } // setupUi

    void retranslateUi(QWidget *AttemperForm)
    {
        AttemperForm->setWindowTitle(QApplication::translate("AttemperForm", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AttemperForm: public Ui_AttemperForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTEMPERFORM_H
