#include "myflashlist.h"
#include "ui_myflashlist.h"

#include <QDebug>

myFlashList::myFlashList(int hei, int num, QWidget *parent) :
    QWidget(parent),ui(new Ui::myFlashList)
{
    ui->setupUi(this);
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<parent->width()<<parent->height()
           <<"\n";
    setFixedSize(parent->width(),parent->height()*9.5/10);
    ui->widget_show->setFixedSize(this->width(),hei*num);
    this->m_item_height=hei;

    scrollbar=NULL;
    PYFLP=NULL;
    initVars();
    initWgts();
    initStgs();
    initConns();
}

myFlashList::~myFlashList()
{
    PYFLP->clear();
    if(PYFLP)
    {
        delete PYFLP;
        PYFLP=NULL;
    }
    if(scrollbar)
    {
        delete scrollbar;
        scrollbar=NULL;
    }
}

void myFlashList::initVars()
{

}

void myFlashList::initWgts()
{
    scrollbar = new QScrollBar(this);
    PYFLP = new NewPYFlashListPrivate(this->m_item_height,ui->widget_show);
}

void myFlashList::initStgs()
{
    scrollbar->hide();
}

void myFlashList::initConns()
{
    connect(scrollbar,SIGNAL(valueChanged(int)),PYFLP,SLOT(setCurrentIndex(int)));
    connect(PYFLP,SIGNAL(sig_setMaximum(int)),this,SLOT(setMaximum(int)));
    connect(PYFLP,SIGNAL(sig_setCurrentIndex(int)),scrollbar,SLOT(setValue(int)));
    connect(PYFLP,SIGNAL(sig_itemClicked(int)),this,SIGNAL(sig_itemClicked(int)));
    connect(PYFLP,SIGNAL(sig_itemClicked(QString)),this,SIGNAL(sig_itemClicked(QString)));
}

void myFlashList::set_item_height(int hei)
{
    this->m_item_height=hei;
    this->PYFLP->setItemHeight(hei);
}

void myFlashList::calcGeo()
{
}

void myFlashList::setMaximum(int max)
{
    if(max == 0)
    {
        scrollbar->hide();
    }else
    {
        scrollbar->show();
    }
    scrollbar->setRange(0,max);

}

void myFlashList::resizeEvent(QResizeEvent *)
{

}

void myFlashList::addItem(const QString &str)
{
    PYFLP->addItem(str);
}

void myFlashList::clear()
{
    PYFLP->clear();
}

void myFlashList::render()
{
    PYFLP->render();
}


