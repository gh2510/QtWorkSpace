#ifndef ADDERRORDIALOG_H
#define ADDERRORDIALOG_H

#include <QDialog>

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include<QTextEdit>
#include <QGridLayout>
#include "myipaddredit.h"
#include "commonbutton.h"
namespace Ui {
class AddErrorDialog;
}

class AddErrorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddErrorDialog(QWidget *parent = 0);
    ~AddErrorDialog();
    void setDialogFlag(bool flag);
    void setDialogFlag2(bool flag);
    QLineEdit * codeLineEdit;
    QTextEdit * infoLineEdit;
    QTextEdit * measureLineEdit;
private:
    QLabel * codeLabel;
    QLabel * infoLabel;
    QLabel * measureLabel;

    commonButton *okButton;
    commonButton *cancelButton;
    QGridLayout *gLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
    Ui::AddErrorDialog *ui;
};

#endif // ADDERRORDIALOG_H
