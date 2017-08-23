#ifndef SHOWLOGDIALOG_H
#include"commonbutton.h"
#include <QDialog>
#define SHOWLOGDIALOG_H
#include<QTextBrowser>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<iostream>
#include<QDir>
#include <QSqlQuery>
#include<fstream>

namespace Ui {
  class ShowLogDialog;
}

class ShowLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowLogDialog(QWidget *parent = 0);
    ~ShowLogDialog();
    void show();

public slots:
    void refresh();
    void addRecord(QString) ;  //yangmeng 161026 日志实时更新
private:
    Ui::ShowLogDialog *ui;
    commonButton *ok;
    QTextBrowser *showLog;
    QVBoxLayout *mainLayout;
    QHBoxLayout *hMain;
    int currentNum;    
    //QString logFileName;    //日志文件名，定义为静态变量，每次开机取得 qhy 2016.11.24
 };

#endif // SHOWLOGDIALOG_H
