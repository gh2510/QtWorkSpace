#ifndef ALARMMANAGE_H
#define ALARMMANAGE_H

#include <QWidget>
#include "myflashlist.h"
namespace Ui {
class AlarmManage;
}

class AlarmManage : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmManage(QWidget *parent = 0);
    ~AlarmManage();

private:
    Ui::AlarmManage *ui;
    myFlashList *flashlist;
};

#endif // ALARMMANAGE_H
