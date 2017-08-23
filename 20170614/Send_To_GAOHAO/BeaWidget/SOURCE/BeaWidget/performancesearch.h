#ifndef PERFORMANCESEARCH_H
#define PERFORMANCESEARCH_H

#include <QWidget>
#include"performancepage.h"

#include"search_performance.h"
namespace Ui {
class PerformanceSearch;
}

class PerformanceSearch : public QWidget
{
    Q_OBJECT
    
public:
    explicit PerformanceSearch(QWidget *parent = 0);
    ~PerformanceSearch();
    
private:
    Ui::PerformanceSearch *ui;
public slots:
    void slot_search_res(QString,QString,QString,QString,QString,QString);
    void slot_clear();
private:
     PerformancePage *alarmTable;
     QVBoxLayout *main_layout;
     Search_performance *searchAlarm;
     QString pre_sql;
     QStringList ql;
     QList<int> qi;
};

#endif // PERFORMANCESEARCH_H
