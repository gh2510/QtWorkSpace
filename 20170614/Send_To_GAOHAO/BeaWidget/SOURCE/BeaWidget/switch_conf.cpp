#include "switch_conf.h"
#include "ui_switch_conf.h"
#include <QApplication>
#include <QDesktopWidget>

switch_conf::switch_conf(QWidget *parent) :
    QWidget(parent),ui(new Ui::switch_conf)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->widget->setFixedSize(this->width(),this->height());
    ui->widget_switch->setMinimumWidth(ui->widget->width()-35);
    ui->widget_switch->setMinimumHeight(ui->widget->height()*9.5/10);
    sconf = new switchConf(ui->widget_switch);
    scrollArea=NULL;
}

switch_conf::~switch_conf()
{
    if(sconf)delete sconf;
    if(scrollArea)delete scrollArea;
}
