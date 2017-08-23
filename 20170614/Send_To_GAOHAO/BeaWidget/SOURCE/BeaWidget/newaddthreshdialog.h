#ifndef NEWADDTHRESHDIALOG_H
#define NEWADDTHRESHDIALOG_H

#include <QDialog>

namespace Ui {
class NewAddThreshDialog;
}

class NewAddThreshDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAddThreshDialog(QWidget *parent = 0);
    ~NewAddThreshDialog();
    void setNameEn(bool flag);
    QString getAlarmName();
    QString getThresh();
    void setIfEnabled(bool ifEnable);
    void setDialogShow(QString name,QString thresh);

private:
    Ui::NewAddThreshDialog *ui;
};

#endif // NEWADDTHRESHDIALOG_H
