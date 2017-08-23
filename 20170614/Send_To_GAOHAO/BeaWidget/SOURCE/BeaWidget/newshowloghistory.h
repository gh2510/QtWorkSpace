#ifndef NEWSHOWLOGHISTORY_H
#define NEWSHOWLOGHISTORY_H

#include <QDialog>
#include "calendar_dialog.h"

namespace Ui {
class NewShowLogHistory;
}

class NewShowLogHistory : public QDialog
{
    Q_OBJECT

public:
    explicit NewShowLogHistory(QWidget *parent = 0);
    ~NewShowLogHistory();

public slots:
    void search();   //查询按钮
    void clearDate();
    void showcalendar();
    void setdate(const QDate& date_checked);

private:
    Ui::NewShowLogHistory *ui;
    CalendarDialog *calendar;
    int currentNum;
    QString logFile;    //日志文件名
};

#endif // NEWSHOWLOGHISTORY_H
