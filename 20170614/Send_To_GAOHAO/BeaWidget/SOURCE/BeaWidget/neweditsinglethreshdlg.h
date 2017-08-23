#ifndef NEWEDITSINGLETHRESHDLG_H
#define NEWEDITSINGLETHRESHDLG_H

#include <QDialog>

namespace Ui {
class NewEditSingleThreshDlg;
}

class NewEditSingleThreshDlg : public QDialog
{
    Q_OBJECT

public:
    explicit NewEditSingleThreshDlg(QWidget *parent = 0);
    ~NewEditSingleThreshDlg();
    QString getSwitchName();
    QString getSwitchPort();
    QString getType();
    QString getValue();
    void setDialogShow(bool ifEnabled,QString name,QString port,QString index,QString value);

public slots:
    void slot_indexChanged(QString  name);
    void addProtNum();
    void reducePortBum();

signals:
    void changePortNum(int);

private:
    Ui::NewEditSingleThreshDlg *ui;
};

#endif // NEWEDITSINGLETHRESHDLG_H
