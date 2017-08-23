#include "alarmtableview.h"
#include <qheaderview.h>
AlarmTableView::AlarmTableView()
{
    alarmtablemodel = new QSqlTableModel(this);
    alarmtablemodel->setTable("alarm");
    alarmtablemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);


    QPalette palette;
    palette.setColor(QPalette::Window, QColor(54,54,54));
    palette.setColor(QPalette::WindowText,QColor("white"));
    setPalette (palette);

//    connect(ui->pushButton_edit,SIGNAL(clicked()),this,SLOT(editEntry()));
}
  void  AlarmTableView::init()
    {
        alarmtablemodel->select(); //选取整个表的所有行    
        alarmtablemodel->removeColumn(7);

        setModel(alarmtablemodel);

        setColumnWidth (0,200);
        setColumnWidth (1,200);
        setColumnWidth (2,100);
        setColumnWidth (3,100);
//        setColumnWidth (4,200);
//        setColumnWidth (5,100);
        setAutoFillBackground (true);
        setStyleSheet ("border-style: outset;border-width: 1px;border-radius: 3px;border-color:rgb(65,105,225);padding: 0px");
        setSortingEnabled(true);
        sortByColumn (0,Qt::DescendingOrder);

        setSelectionBehavior(QAbstractItemView::SelectRows);
        this->horizontalHeader()->setStretchLastSection(true);
        this->verticalHeader ()->setVisible (false);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setSelectionMode(QAbstractItemView::MultiSelection);
    }

 void AlarmTableView::slot_query()
    {
        alarmtablemodel->select(); //选取整个表的所有行

        setModel(alarmtablemodel);
        setSortingEnabled(true);
        sortByColumn (0,Qt::DescendingOrder);

        setSelectionBehavior(QAbstractItemView::SelectRows);
        this->horizontalHeader()->setStretchLastSection(true);
        this->verticalHeader ()->setVisible (false);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setSelectionMode(QAbstractItemView::MultiSelection);
    }


AlarmTableView::~AlarmTableView()
{
    if(alarmtablemodel)
    delete alarmtablemodel;
}


void AlarmTableView::slot_addEntry(){
        int rowNum = alarmtablemodel->rowCount(); //获得表的行数

            int id = rowNum+1;
            alarmtablemodel->insertRow(rowNum); //添加一行
            alarmtablemodel->setData(alarmtablemodel->index(rowNum,0),id);

            alarmtablemodel->submitAll(); //可以直接提交
            resizeColumnToContents(0);
            resizeColumnToContents(1);
            resizeColumnToContents(2);
            resizeColumnToContents(3);
            resizeColumnToContents(4);
            resizeColumnToContents(5);
            resizeColumnToContents(6);
            resizeColumnToContents(7);
}

void AlarmTableView::slot_checkEntry(){
    QModelIndexList index = selectionModel()->selectedRows ();
    QModelIndex selectedindex;
    if (!index.isEmpty ())
    {
        int row ;
        for (int i=0;i<index.size ();i++)
        {
        row = index.at(i).row ();
        selectedindex = alarmtablemodel->index(row,7, QModelIndex());
        alarmtablemodel->setData(selectedindex,"是", Qt::EditRole);
        alarmtablemodel->submitAll();
        }
    }
}
