/********************************************************************************
** Form generated from reading UI file 'roleselect.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROLESELECT_H
#define UI_ROLESELECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoleSelect
{
public:

    void setupUi(QWidget *RoleSelect)
    {
        if (RoleSelect->objectName().isEmpty())
            RoleSelect->setObjectName(QString::fromUtf8("RoleSelect"));
        RoleSelect->resize(400, 300);
        RoleSelect->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	\n"
"	background-color: rgb(170, 85, 255);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	\n"
"	font: 16pt \"\346\245\267\344\275\223\";\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	font: 75 14pt \"\346\245\267\344\275\223\";\n"
"	\n"
"	\n"
"	background-color: rgb(42, 255, 209);\n"
"}\n"
"\n"
"QTextEdit\n"
"{\n"
"	\n"
"	font: 16pt \"\346\245\267\344\275\223\";\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	\n"
"	font: 75 14pt \"\346\245\267\344\275\223\";\n"
"}\n"
"\n"
"QCheckBox\n"
"{\n"
"	\n"
"	font: 11pt \"\346\245\267\344\275\223\";\n"
"}"));

        retranslateUi(RoleSelect);

        QMetaObject::connectSlotsByName(RoleSelect);
    } // setupUi

    void retranslateUi(QWidget *RoleSelect)
    {
        RoleSelect->setWindowTitle(QApplication::translate("RoleSelect", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RoleSelect: public Ui_RoleSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROLESELECT_H
