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
 * �������ܣ������澯�Ի���
 */
void MainWindow::WarnMessage(QString errInfo)
{
    QMessageBox::information(NULL,"����!",errInfo,QMessageBox::Ok);
}
