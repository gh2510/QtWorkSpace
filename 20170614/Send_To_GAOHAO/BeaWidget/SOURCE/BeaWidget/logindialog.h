#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialog>
#include "mainframe.h"
#include "pushbutton_diy.h"
#include "commonbutton.h"
#include <QPalette>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
namespace Ui {
class LoginDialog;
}
extern bool userLevel;
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
      ~LoginDialog();    

signals:
    void signal_addRecord(QString);      //yangmeng 161026 日志实时更新    

 private slots:
    void on_loginBtn_clicked(); 
    void quit();
    void on_defaultLoginBtn_clicked();  //默认用户登录按钮响应  yangmeng 161023

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
