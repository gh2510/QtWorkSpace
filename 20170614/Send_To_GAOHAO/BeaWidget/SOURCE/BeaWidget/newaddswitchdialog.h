#ifndef NEWADDSWITCHDIALOG_H
#define NEWADDSWITCHDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class NewAddSwitchDialog;
}

class NewAddSwitchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAddSwitchDialog(QWidget *parent = 0);
    ~NewAddSwitchDialog();
    void setDialogFlag(bool flag);
    void setIsEdit(bool flag);
    void setReadOnly(bool readonly);
    void setText(const QString &text,const int index);
    void setInfShow(QString name,QString address,QString address2,QString description,QString location,QString remark);
    QString getIP_In();
    QString getIp_Out();
    QString getName();
    QString getDescription();
    QString getLocation();
    QString getRemark();
signals:
    void textchanged(const QString &text);
    void textedited(const QString &text);

private slots:
    void textchangedslot(const QString &text);
    void texteditedslot(const QString &text);

private:
    Ui::NewAddSwitchDialog *ui;
    QList <QLineEdit*> ipLineEdits;
    void iniTabOrder();
};

#endif // NEWADDSWITCHDIALOG_H
