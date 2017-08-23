#ifndef NEWADDERRORDIALOG_H
#define NEWADDERRORDIALOG_H

#include <QDialog>

namespace Ui {
class NewAddErrorDialog;
}

class NewAddErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAddErrorDialog(QWidget *parent = 0);
    ~NewAddErrorDialog();
    void setDialogFlag(bool flag);
    void setDialogFlag2(bool flag);
    void setText(QString errorcode = " ",QString errorinfo= " ",QString measure = " ");
    QString getCode();
    QString getInfo();
    QString getMeasure();

private:
    Ui::NewAddErrorDialog *ui;
};

#endif // NEWADDERRORDIALOG_H
