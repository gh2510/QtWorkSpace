#include "mainwindow.h"
#include "ui_mainwindow.h"

CombatPosition MainWindow::currentCombatPosition;
Attemper *MainWindow::attmper = new Attemper();
DDSPublich MainWindow::ddsPublic;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 函数功能：弹出告警对话框
 */
void MainWindow::WarnMessage(QString errInfo)
{
    QMessageBox::information(NULL,"警告!",errInfo,QMessageBox::Ok);
}
