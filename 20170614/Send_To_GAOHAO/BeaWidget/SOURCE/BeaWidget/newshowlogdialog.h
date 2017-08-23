#ifndef NEWSHOWLOGDIALOG_H
#define NEWSHOWLOGDIALOG_H

#include <QDialog>

namespace Ui {
class NewShowLogDialog;
}

class NewShowLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewShowLogDialog(QWidget *parent = 0);
    ~NewShowLogDialog();
    void show();

public slots:
    void refresh();
    void addRecord(QString newRecord) ;  //yangmeng 161026 日志实时更新

private:
    Ui::NewShowLogDialog *ui;
    int currentNum;
    //QString logFileName;    //日志文件名，定义为静态变量，每次开机取得 qhy 2016.11.24
};

#endif // NEWSHOWLOGDIALOG_H
