#include "mainwindow.h"
#include "ui_mainwindow.h"


CombatPosition MainWindow::currentCombatPosition;
Attemper *MainWindow::attmper = new Attemper();
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
