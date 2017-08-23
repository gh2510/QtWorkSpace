#include "errormanage.h"
#include "ui_errormanage.h"
#include <QtGui>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include<QApplication>
#include<QDesktopWidget>
#include"connection.h"
#include"logindialog.h"
ErrorManage::ErrorManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorManage)
{
    ui->setupUi(this);
    setFixedSize(QApplication::desktop()->width()*5/6,QApplication::desktop()->height()*5/6);
    switchTableModel = new myStandardItemModel();
    tableview =new QTableView();

    tableview->setModel(switchTableModel);
    tableview->sortByColumn (0,Qt::AscendingOrder);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview->horizontalHeader()->setStretchLastSection(true);
    tableview->verticalHeader ()->setVisible (false);
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableview->setSelectionMode(QAbstractItemView::SingleSelection);
    tableview->setColumnWidth(0,50);
    tableview->setColumnWidth(1,200);
    tableview->setColumnWidth(2,350);
    tableview->setColumnWidth(3,200);
    tableview->setAutoFillBackground (true);
    tableview->horizontalHeader()->setStyleSheet
    ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
    "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
    "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");

    tableview->verticalHeader()->setDefaultSectionSize(40);

    btn_add =new commonButton();
    btn_add->setText("添加");
    btn_add->setFixedSize(80,30);
    btn_add->setVisible(false);
    btn_delete =new commonButton();
    btn_delete->setText("删除");
    btn_delete->setFixedSize(80,30);
    btn_delete->setVisible(false);
    btn_update =new commonButton();
    btn_update->setText("修改");
    btn_update->setFixedSize(80,30);

    btn_show =new commonButton();
    btn_show->setText("查看");
    btn_show->setFixedSize(80,30);

    bottom_layout=new QHBoxLayout();
    bottom_layout->addStretch(3);
    bottom_layout->addWidget(btn_add,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(btn_delete,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(btn_update,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(btn_show,0,Qt::AlignVCenter);
    bottom_layout->addStretch(3);

    if(userLevel==0)//guanliyuan
    {
         btn_add->setVisible(true);
        btn_delete->setVisible(true);
    }
    init_table();

    mainLayout=new QVBoxLayout();
    mainLayout->setMargin(10);
    mainLayout->addWidget(tableview,0,Qt::AlignHCenter);
    mainLayout->addLayout(bottom_layout,0);
    setLayout(mainLayout);

//    QPalette palette;
//    palette.setColor(QPalette::Window, QColor(54,54,54));
//    palette.setColor(QPalette::WindowText,QColor("white"));
//   tableview->setPalette (palette);

    connect(tableview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editEntry()));
    connect(btn_add,SIGNAL(click()),this,SLOT(addEntry()));
    connect(btn_delete,SIGNAL(click()),this,SLOT(removeEntry()));
    connect(btn_update,SIGNAL(click()),this,SLOT(editEntry()));
    connect(btn_show,SIGNAL(click()),this,SLOT(showEntry()));

}
void ErrorManage::init_table()
{
    QSqlQuery  sqlquery("",DBConnection::db);
    sqlquery.exec("select  errorcode,errorinfo,measure,time  from errormanage");
    int itemCount=0;
    switchTableModel->clear();
    switchTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("出错代码")));
    switchTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("出错信息")));
    switchTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("建议措施")));
    switchTableModel->setHorizontalHeaderItem(3,new QStandardItem(tr("录入时间")));

    while(sqlquery.next())
    {
        switchTableModel->setItem(itemCount,0,new QStandardItem(sqlquery.value(0).toString()));
        switchTableModel->setItem(itemCount,1,new QStandardItem(sqlquery.value(1).toString()));
        switchTableModel->setItem(itemCount,2,new QStandardItem(sqlquery.value(2).toString()));
        switchTableModel->setItem(itemCount,3,new QStandardItem(sqlquery.value(3).toString()));
        tableview->setRowHeight(itemCount,40);
        itemCount++;
    }
  sqlquery.finish();
  sqlquery.clear();

  //修改为自适应窗口宽度---qhy，2016.11.05 ，未更新到监控管理设备
  int wi = QApplication::desktop()->width()*7/8;
  tableview->setModel(switchTableModel);
  tableview->setColumnWidth(0,wi*1/12);
  tableview->setColumnWidth(1,wi*3/12);
  tableview->setColumnWidth(2,wi*5.5/12);
  tableview->setColumnWidth(3,wi*1.3/12);
  tableview->setFixedWidth(wi-60); 
}

void ErrorManage::addEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    AddErrorDialog aDialog;
    aDialog.setDialogFlag(true);
    aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);
    if (aDialog.exec()) {
        QString errorcode = aDialog.codeLineEdit->text().trimmed();
        QString errorinfo = aDialog.infoLineEdit->toPlainText().trimmed();
        QString measure= aDialog.measureLineEdit->toPlainText().trimmed();
        if(errorcode==""||errorinfo==""||measure=="")
        {
            QMessageBox::information(this,"信息错误","请填写详细内容信息!");
            return;
        }
        QSqlQuery sqlquery("",DBConnection::db);
        sqlquery.prepare("select count(*) from errormanage where errorcode=?");
        sqlquery.bindValue(0,errorcode);
        sqlquery.exec();
        sqlquery.next();        
        int res_num=sqlquery.value(0).toInt();
        if(res_num>0)
        {
            QMessageBox::information(this,"信息错误","出错代码重复");
        }
        else
        {

            sqlquery.prepare("insert into errormanage (errorcode,errorinfo,measure,time)  values(?,?,?,?)");
            sqlquery.bindValue(0,errorcode);
            sqlquery.bindValue(1,errorinfo);
            sqlquery.bindValue(2,measure);
            sqlquery.bindValue(3,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

            sqlquery.exec();

            init_table();

        }
        sqlquery.finish();
        sqlquery.clear();
    }
}

void ErrorManage::removeEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    switch(QMessageBox::question(this,tr("删除记录"),tr("是否删除?"),
              QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
      {
      case QMessageBox::Cancel:
        return;
   }
    QModelIndexList index =tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString errorcode;
        int table_index;
        int row = index.at(0).row ();

        QModelIndex nameIndex = switchTableModel->index(row, 0, QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex, Qt::DisplayRole);
        errorcode = varName.toString();

        QSqlQuery  sqlquery("",DBConnection::db);
        QString delete_sql = "delete from errormanage where errorcode=?";
        sqlquery.prepare(delete_sql);
        sqlquery.addBindValue(errorcode);
        sqlquery.exec();
        sqlquery.finish();
        sqlquery.clear();
         init_table();

    }
}
void ErrorManage::slot_init()
{
    init_table();
}

void ErrorManage::editEntry()
{

    QModelIndexList index =tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString errorcode;
        QString errorinfo;
        QString measure;
        //QString remark;
        int table_index;
        int row = index.at(0).row ();

        QModelIndex tb_in_Index = switchTableModel->index(row, 0, QModelIndex());
        QVariant tb_in_da = switchTableModel->data(tb_in_Index, Qt::DisplayRole);
        errorcode = tb_in_da.toString();


        QModelIndex nameIndex = switchTableModel->index(row, 1, QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex, Qt::DisplayRole);
        errorinfo = varName.toString();


        QModelIndex locationIndex = switchTableModel->index(row, 2, QModelIndex());
        QVariant vaLocation= switchTableModel->data(locationIndex, Qt::DisplayRole);
        measure = vaLocation.toString();


/*
        QModelIndex communityIndex = switchTableModel->index(row, 4, QModelIndex());
        QVariant varCommunity = switchTableModel->data(communityIndex, Qt::DisplayRole);
        remark = varCommunity.toString();
*/
        //! [4b]
        AddErrorDialog aDialog;
        aDialog.setWindowTitle(tr("修改故障信息"));
         aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);
//        aDialog.ipAddressLineEdit->setReadOnly(true);
        aDialog.codeLineEdit->setText(errorcode);
        aDialog.infoLineEdit->setText(errorinfo);
        aDialog.measureLineEdit->setText(measure);
        // aDialog.remarkEdit->setCurrentIndex( aDialog.remarkEdit->findText(remark));
        aDialog.setDialogFlag(false);
        if (aDialog.exec())
        {
            QString newCode = aDialog.codeLineEdit->text();
            QString newInfo = aDialog.infoLineEdit->toPlainText ();
            QString newMeasure = aDialog.measureLineEdit->toPlainText ();
            //QString newRemark = aDialog.remarkEdit->currentText();

            if (!newCode.isEmpty ()&&!newInfo.isEmpty ()&&!newMeasure.isEmpty ())
            {
                    QSqlQuery query("",DBConnection::db);;
                    QString update_sql = "update errormanage set errorinfo=?,measure=? ,time=? where errorcode=? ";
                    query.prepare(update_sql);
                    query.bindValue(0,newInfo);
                    query.bindValue(1,newMeasure);
                    query.bindValue(2,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    query.bindValue(3,newCode);
                    //query.bindValue(3,table_index);
                    query.exec();
                    query.finish();
                    query.clear();
                    init_table();
            }
            else{
                QMessageBox::information(this,"信息不完整","请填写完整信息");
            }

        }

       tableview->selectRow (row);
       tableview->setFocus ();
    }

}

void ErrorManage::showEntry()
{


    QModelIndexList index =tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString errorcode;
        QString errorinfo;
        QString measure;
        //QString remark;
        int table_index;
        int row = index.at(0).row ();

        QModelIndex tb_in_Index = switchTableModel->index(row, 0, QModelIndex());
        QVariant tb_in_da = switchTableModel->data(tb_in_Index, Qt::DisplayRole);
        errorcode = tb_in_da.toString();


        QModelIndex nameIndex = switchTableModel->index(row, 1, QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex, Qt::DisplayRole);
        errorinfo = varName.toString();


        QModelIndex locationIndex = switchTableModel->index(row, 2, QModelIndex());
        QVariant vaLocation= switchTableModel->data(locationIndex, Qt::DisplayRole);
        measure = vaLocation.toString();


/*
        QModelIndex communityIndex = switchTableModel->index(row, 4, QModelIndex());
        QVariant varCommunity = switchTableModel->data(communityIndex, Qt::DisplayRole);
        remark = varCommunity.toString();
*/
        //! [4b]
        AddErrorDialog aDialog;
        aDialog.setWindowTitle(tr("查看故障信息"));
         aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);

        aDialog.codeLineEdit->setText(errorcode);
        aDialog.infoLineEdit->setText(errorinfo);
        aDialog.measureLineEdit->setText(measure);

        aDialog.setDialogFlag2(false);

       aDialog.exec();
       tableview->selectRow (row);
       tableview->setFocus ();
    }



}

ErrorManage::~ErrorManage()
{
    if(switchTableModel)delete switchTableModel;
    if(tableview)delete tableview;
    if(btn_add)delete btn_add;
    if(btn_delete)delete btn_delete;
    if(btn_update)delete btn_update;
    if(bottom_layout)delete bottom_layout;
    if(mainLayout)delete mainLayout;


    delete ui;
}
