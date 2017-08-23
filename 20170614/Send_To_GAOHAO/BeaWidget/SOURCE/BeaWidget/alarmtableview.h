#ifndef ALARMTABLEVIEW_H
#define ALARMTABLEVIEW_H

#include <QTableView>
#include <QSqlTableModel>
class AlarmTableView : public QTableView
{
public:
    AlarmTableView();
    void init();
    ~AlarmTableView();
public slots:
    void slot_addEntry();
    void slot_checkEntry();
    void slot_query();

private:
     QSqlTableModel * alarmtablemodel;
};

#endif // ALARMTABLEVIEW_H-


