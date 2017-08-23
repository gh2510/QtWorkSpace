#include "showswitch.h"
#include "ui_showswitch.h"
#include<QSqlQuery>
#include<QApplication>
#include<QDesktopWidget>
#include"connection.h"
ShowSwitch::ShowSwitch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowSwitch)
{
    ui->setupUi(this);
    btn_ok=new commonButton(this);
    btn_ok->setText("确定");
    btn_ok->setFixedWidth(80);

    switchTableModel = new myStandardItemModel();

    tableview =new QTableView();
    tableview->setModel(switchTableModel);
    tableview->sortByColumn (0,Qt::AscendingOrder);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview->horizontalHeader()->setStretchLastSection(true);
    tableview->verticalHeader ()->setVisible (false);
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableview->setSelectionMode(QAbstractItemView::SingleSelection);
    /*
    int wi=QApplication::desktop()->width()/5;
    tableview->setColumnWidth(0,wi);
    tableview->setColumnWidth(1,wi);
    tableview->setColumnWidth(2,wi);
    tableview->setColumnWidth(3,wi);
    tableview->setFixedWidth(wi*4);
    tableview->setFixedHeight(QApplication::desktop()->height()*4/5);
    tableview->setAutoFillBackground (true);
    */
    tableview->horizontalHeader()->setStyleSheet
    ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
    "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
    "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");

    tableview->verticalHeader()->setDefaultSectionSize(40);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(26,28,26));  //background color
    palette.setColor(QPalette::WindowText,QColor("white"));
    this->setPalette(palette);
    init_table();

    bottom_layout=new QHBoxLayout(this);
    bottom_layout->addWidget(btn_ok);
    mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(tableview,0,Qt::AlignCenter);
    mainLayout->addLayout(bottom_layout,0);
    this->setLayout(mainLayout);

    connect(btn_ok,SIGNAL(click()),this,SLOT(slot_close()));

    setWindowTitle(tr("交换机详细信息"));
//    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);

}

void ShowSwitch::init_table()
{

    QSqlQuery  sqlquery("",DBConnection::db);
    sqlquery.exec("select  ID,name,alarmtype  from alarmcurrent ");
    int itemCount=0;

    switchTableModel->clear();

    switchTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("端口号")));
    switchTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("设备信息")));
    switchTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("连接状态")));
    while(sqlquery.next())
    {
        switchTableModel->setItem(itemCount,0,new QStandardItem(sqlquery.value(0).toString()));
        switchTableModel->setItem(itemCount,1,new QStandardItem(sqlquery.value(1).toString()));
        switchTableModel->setItem(itemCount,2,new QStandardItem(sqlquery.value(2).toString()));
        tableview->setRowHeight(itemCount,40);
        itemCount++;
    }

   sqlquery.finish();
   sqlquery.clear();
  tableview->setModel(switchTableModel);
  tableview->setColumnWidth(0,100);
  tableview->setColumnWidth(1,180);
  tableview->setColumnWidth(2,155);
  tableview->setColumnWidth(3,155);
  tableview->setColumnWidth(4,50);
  tableview->setFixedWidth(800);
}

void ShowSwitch::slot_close()
{
    this->close();
}


ShowSwitch::~ShowSwitch()
{
    delete ui;
}
