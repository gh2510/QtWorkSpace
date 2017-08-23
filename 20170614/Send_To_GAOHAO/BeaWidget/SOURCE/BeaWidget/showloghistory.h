#ifndef SHOWLOGHISTORY_H
#define SHOWLOGHISTORY_H
#include<QVBoxLayout>
#include<QHBoxLayout>
#include"commonbutton.h"
#include <QWidget>
#include<QTextBrowser>
#include <QDate>
#include <QDialog>
#include <dateedit.h>
#include "calendar_dialog.h"
namespace Ui {
  class showLogHistory;
}
class showLogHistory : public QDialog
{
    Q_OBJECT
public:
    explicit showLogHistory(QWidget *parent = 0);
    ~showLogHistory();
    void init_search();
signals:
    
public slots:
    void search();   //查询按钮
    void clearDate();
private:
    commonButton *query;
    QTextBrowser *showLog;
    QVBoxLayout *mainLayout;
    QHBoxLayout *searchCon1;   //查询条件部分
    QPalette palette;
    int currentNum;
    QString logFile;    //日志文件名
    DateEdit *starttime;
   commonButton *clearTime;   //, *clearData;
   Ui::showLogHistory *ui;
};

#endif // SHOWLOGHISTORY_H
