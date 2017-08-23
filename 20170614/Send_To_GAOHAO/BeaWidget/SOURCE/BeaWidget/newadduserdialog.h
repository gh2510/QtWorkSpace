#ifndef NEWADDUSERDIALOG_H
#define NEWADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
class NewAddUserDialog;
}

class NewAddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAddUserDialog(QWidget *parent = 0);
    ~NewAddUserDialog();
    void setNameEn(bool flag);
    void setInfoShow(QString name,QString password,QString level);
    QString getUserName()const;
    QString getPassword()const;
    QString getUserLevel()const;

private:
    Ui::NewAddUserDialog *ui;
};

#endif // NEWADDUSERDIALOG_H
