#include "errordeal.h"
#include "ui_errordeal.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include"adderrordialog.h"
#include"connection.h"
#include"logindialog.h"
ErrorDeal::ErrorDeal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorDeal)
{
    ui->setupUi(this);


    switchTableModel = new myStandardItemModel();
    tableview =new QTableView();
    tableview->setModel(switchTableModel);
    tableview->sortByColumn (0,Qt::AscendingOrder);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview->horizontalHeader()->setStretchLastSection(true);
    tableview->verticalHeader ()->setVisible (false);
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableview->setSelectionMode(QAbstractItemView::SingleSelection);
    tableview->setColumnWidth(0,20);
    tableview->setColumnWidth(1,200);
    tableview->setColumnWidth(2,350);
    tableview->setColumnWidth(3,150);
    tableview->setAutoFillBackground (true);
    tableview->horizontalHeader()->setStyleSheet
    ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
    "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
    "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");

    tableview->verticalHeader()->setDefaultSectionSize(40);
    btn_add =new commonButton();
    btn_add->setText("保存");
    btn_add->setFixedSize(80,30);
    btn_refresh =new commonButton();
    btn_refresh->setText("刷新");
    btn_refresh->setFixedSize(80,30);


    bottom_layout=new QHBoxLayout();
    bottom_layout->addStretch(2);
    bottom_layout->addWidget(btn_refresh,0,Qt::AlignVCenter);
    bottom_layout->addWidget(btn_add,1,Qt::AlignVCenter);
    init_table();

    mainLayout=new QVBoxLayout();
    mainLayout->setMargin(10);

    mainLayout->addLayout(bottom_layout,0);
     mainLayout->addWidget(tableview,0,Qt::AlignHCenter);

    setLayout(mainLayout);
    time=new QTimer(this);
    connect(btn_add,SIGNAL(click()),this,SLOT(updateAlarm()));
    connect(btn_refresh,SIGNAL(click()),this,SLOT(refresh()));
    connect(time,SIGNAL(timeout()),this,SLOT(refresh()));
    time->start(8000);//10秒更新一次
}

void ErrorDeal::init_table()
{

    QSqlQuery  sqlquery("",DBConnection::db);
    sqlquery.exec("select  ID,name,alarmtype,starttime,isdeal  from alarmcurrent where isdeal='否'");
    int itemCount=0;

    switchTableModel->clear();

    switchTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("序号")));
    switchTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("交换机名称")));
    switchTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("告警类型")));
    switchTableModel->setHorizontalHeaderItem(3,new QStandardItem(tr("告警时间")));
    switchTableModel->setHorizontalHeaderItem(4,new QStandardItem(tr("是否处理")));
    while(sqlquery.next())
    {
        switchTableModel->setItem(itemCount,0,new QStandardItem(sqlquery.value(0).toString()));
        switchTableModel->setItem(itemCount,1,new QStandardItem(sqlquery.value(1).toString()));
        switchTableModel->setItem(itemCount,2,new QStandardItem(sqlquery.value(2).toString()));
        switchTableModel->setItem(itemCount,3,new QStandardItem(sqlquery.value(3).toString()));
        QStandardItem *deal=new QStandardItem();

        if(sqlquery.value(4).toString()=="是")
        {
            deal->setText("是");
           //deal->setCheckState(Qt::Unchecked);

        }
        else
        {
            deal->setCheckable(true);
            deal->setCheckState(Qt::Unchecked);

        }

        deal->setTextAlignment(Qt::AlignHCenter);
        deal->setTextAlignment(Qt::AlignCenter);
        deal->setTextAlignment(Qt::AlignVCenter);
        switchTableModel->setItem(itemCount,4,deal);     

        itemCount++;
    }
 sqlquery.finish();
 sqlquery.clear();
  tableview->setModel(switchTableModel);
  tableview->setColumnWidth(0,50);   //100
  tableview->setColumnWidth(1,150);
  tableview->setColumnWidth(2,400);
  tableview->setColumnWidth(3,200);
 // tableview->setColumnWidth(4,QApplication::desktop()->width()*20/120);
  tableview->setFixedWidth(800);
}


ErrorDeal::~ErrorDeal()
{
    delete ui;
    if(switchTableModel)delete switchTableModel;
    if(tableview)delete tableview;
    if(btn_add)delete btn_add;
    if(btn_refresh)delete btn_refresh;
    if(bottom_layout)delete bottom_layout;
    if(mainLayout)delete mainLayout;
    if(time)delete time;

}
void ErrorDeal::updateAlarm()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    for(int i=0;i<switchTableModel->rowCount();i++)
    {
        QModelIndex tb_in_Index1 = switchTableModel->index(i, 1, QModelIndex());
        QVariant tb_in_da1 = switchTableModel->data(tb_in_Index1, Qt::DisplayRole);
        QString name = tb_in_da1.toString();

        QModelIndex tb_in_Index2 = switchTableModel->index(i, 2, QModelIndex());
        QVariant tb_in_da2 = switchTableModel->data(tb_in_Index2, Qt::DisplayRole);
        QString alarmtype = tb_in_da2.toString();

        QStandardItem *temp=switchTableModel->item(i,4);       
        if(temp->text()!="是")
        {
            if(temp->checkState()==Qt::Checked)
            {               
                QSqlQuery query("",DBConnection::db);;
                QString update_sql = "update alarmcurrent set isdeal=? where name=? and alarmtype=? ";
                query.prepare(update_sql);
                query.bindValue(0,"是");
                query.bindValue(1,name);
                query.bindValue(2,alarmtype);
                query.exec();
                query.finish();
                query.clear();

                update_sql = "update alarm set lasttime=?,isdeal=? where name=? and alarmtype=? and isdeal=? ";
                query.prepare(update_sql);
                query.bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(1,"是");
                query.bindValue(2,name);
                query.bindValue(3,alarmtype);
                query.bindValue(4,"否");
                query.exec();
                query.finish();
                query.clear();
                emit sig_cancelWarning(name);
            }
        }
    }
     init_table();
     QMessageBox::information(this,tr("保存结果"),tr("保存成功"),QMessageBox::Ok);
}

void ErrorDeal::refresh()
{
    init_table();
}
