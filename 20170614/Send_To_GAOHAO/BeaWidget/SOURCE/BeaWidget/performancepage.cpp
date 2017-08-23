#include "performancepage.h"
#include<QBoxLayout>
#include<QSqlQuery>
#include<QMessageBox>
#include<QHeaderView>
#include <QApplication>
#include <QDesktopWidget>
#include "insertthread.h"
PerformancePage::PerformancePage(QWidget *parent) :
    QWidget(parent)
{   this->sql="";
    currentPage = 0;
    totalRecrodCount=0;
    totalPage=0;
    InitWindow();
}

PerformancePage::~PerformancePage()
{
   if(tableView)delete tableView;
   if(totalPageLabel)delete totalPageLabel;
   if(currentPageLabel)delete currentPageLabel;
   if(switchPageLineEdit)delete switchPageLineEdit;
   if(prevButton)delete prevButton;
   if(nextButton)delete nextButton;
   if(switchPageButton)delete switchPageButton;
   if(bottom_layout)delete bottom_layout;
   if(main_layout)delete main_layout;
   if(switchpage)delete switchpage;
   if(page)delete page;

}
void PerformancePage::InitWindow()
{

    prevButton=new commonButton();
    nextButton=new commonButton();
    switchPageButton=new commonButton();
    firstButton=new commonButton();
    lastButton=new commonButton();

    firstButton->setText("首页");
    firstButton->setFixedSize(110,30);
    lastButton->setText("尾页");
    lastButton->setFixedSize(110,30);

    prevButton->setText("前一页");
    prevButton->setFixedSize(110,30);
    nextButton->setText("下一页");
    nextButton->setFixedSize(110,30);
    switchPageButton->setText("转到");
    switchPageButton->setFixedSize(110,30);

    switchPageLineEdit=new QLineEdit();
    switchPageLineEdit->setFixedWidth(40);

    switchpage=new QLabel();
    switchpage->setText("转到第");
    page=new QLabel();
    page->setText("页");

    totalPageLabel=new QLabel();
    currentPageLabel=new QLabel();

    queryModel=new myStandardItemModel();
    tableView=new QTableView();

    tableView->setFixedHeight(QApplication::desktop()->height()*1/10);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setStyleSheet
    ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
    "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
    "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");

    tableView->verticalHeader()->setDefaultSectionSize(40);

    bottom_layout=new QHBoxLayout();
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(totalPageLabel,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(currentPageLabel,0,Qt::AlignVCenter);
    bottom_layout->addStretch(3);
    bottom_layout->addWidget(firstButton,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(prevButton,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(nextButton,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(lastButton,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);

    bottom_layout->addWidget(switchpage);
    bottom_layout->addWidget(switchPageLineEdit,0,Qt::AlignVCenter);
    bottom_layout->addWidget(page);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(switchPageButton,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    main_layout=new QVBoxLayout();
    main_layout->addStretch(1);
    main_layout->addWidget(tableView,0,Qt::AlignHCenter);
    main_layout->addStretch(1);
    main_layout->addLayout(bottom_layout,0);
    main_layout->addStretch(1);
    setLayout(main_layout);
    connect(prevButton,SIGNAL(click()),this,SLOT(OnPrevButtonClick()));
    connect(nextButton,SIGNAL(click()),this,SLOT(OnNextButtonClick()));
    connect(switchPageButton,SIGNAL(click()),this,SLOT(OnSwitchPageButtonClick()));
    connect(firstButton,SIGNAL(click()),this,SLOT(OnFirstButtonClick()));
    connect(lastButton,SIGNAL(click()),this,SLOT(OnLastButtonClick()));



}
 void PerformancePage::SetTableView(QString sql_txt,QStringList title_txt,QList<int> title_width)
 {
     this->sql=sql_txt;
     this->table_title=title_txt;
     this->table_width=title_width;

     RecordQuery(0);//执行查询语句
     totalRecrodCount=GetTotalRecordCount();
     totalPage=GetPageCount();
     if ( totalPage == 0 )     //After query, initiate the currentPage, if there is no data ,set current page 0, otherwise set 1
         currentPage = 0;
     else
         currentPage = 1;
     UpdateStatus();

     for(int i=0;i<table_width.count();i++)
     {
         tableView->setColumnWidth(i,this->table_width.at(i)-1);    //如果需要显示竖直卷滚条，宽度需要-4，才能不出现横向卷滚条 qhy，2016.11.06
     }
 }

  int  PerformancePage::GetTotalRecordCount()
  {
      QString sql_get_num=this->sql.mid(sql.indexOf("from"));
      sql_get_num=QString("select count(*) ")+sql_get_num;
      QSqlQuery sqlquery("",db_sqlite);
      sqlquery.exec(sql_get_num);
      sqlquery.next();
      int tmp= sqlquery.value(0).toInt();
      sqlquery.finish();
      return tmp;

  }

 void PerformancePage::UpdateStatus()
 {
     if ( totalPage == 0 ) {
         currentPage == 0;  //如果没有数据，为0页
         prevButton->setEnabled(false);
         nextButton->setEnabled(false);
         firstButton->setEnabled(false);
         lastButton->setEnabled(false);
         }
     QString szCurrentText = QString("当前第%1页").arg(QString::number(currentPage));
     currentPageLabel->setText(szCurrentText);
     QString szPageCountText = QString("总共%1页").arg(QString::number(totalPage));
     totalPageLabel->setText(szPageCountText);
     if (totalPage > 0 ) {
         if (currentPage==1 ) {
             prevButton->setEnabled(false);
             nextButton->setEnabled(true);
             firstButton->setEnabled(true);
             lastButton->setEnabled(true);
             }
         else if (currentPage==totalPage ) {
             prevButton->setEnabled(true);
             nextButton->setEnabled(false);
             firstButton->setEnabled(true);
             lastButton->setEnabled(true);
             }
         else if ( currentPage<  totalPage ) {
                 prevButton->setEnabled(true);
                 nextButton->setEnabled(true);
                 firstButton->setEnabled(true);
                 lastButton->setEnabled(true);
         }
     }
 }
 int PerformancePage::GetPageCount()
 {
     if (totalRecrodCount ==0 )
         return 0 ;   //没有记录，返回总页数为0
     else
        return (totalRecrodCount % PageRecordCount == 0) ? (totalRecrodCount / PageRecordCount) : (totalRecrodCount / PageRecordCount + 1);
 }

void PerformancePage::RecordQuery(int limitIndex)
{
    QSqlQuery query("",db_sqlite);
    QString sql_t;
    sql_t=sql+QString(" limit %1,%2").arg(limitIndex).arg(QString::number(PageRecordCount));
    query.exec(sql_t);

    int itemCount=0;
    queryModel->clear();
    for(int i=0;i<table_title.count();i++)
    {
         queryModel->setHorizontalHeaderItem(i,new QStandardItem(this->table_title.at(i)));

    }
    while(query.next())
    {
       for(int i=0;i<table_title.count();i++)
        {
            queryModel->setItem(itemCount,i,new QStandardItem(query.value(i).toString()));
        }
       tableView->setRowHeight(itemCount,40);
       itemCount++;
    }
    tableView->setModel(queryModel);

    tableView->setFixedSize( QApplication::desktop()->width()*5/6,QApplication::desktop()->height()*4/6);
    for(int i=0;i<table_width.count();i++)
    {
        tableView->setColumnWidth(i,this->table_width.at(i)-1);  //不显示竖直卷滚条，则宽度需要 -4---qhy 2016.11.06
    }

    query.finish();

}

void PerformancePage::OnPrevButtonClick()
{
    int limitIndex = (currentPage - 2) * PageRecordCount;
    if (currentPage>1 && totalPage >0)  {   //当前页大于1，才能向前翻页---qhy 2016.10.27
        RecordQuery(limitIndex);
        currentPage -= 1;
    }else {
        if (totalPage==0 )
             currentPage = 0;
        }
    UpdateStatus();
}

void PerformancePage::OnNextButtonClick()
{
    int limitIndex = currentPage * PageRecordCount;
    if ( currentPage < totalPage && totalPage >0 ) { //当前页小于总页数，才能向后翻页---qhy 2016.10.27
        RecordQuery(limitIndex);
        currentPage += 1;
     } else {
        if (totalPage==0 )
            currentPage = 0;
        }
    UpdateStatus();
}

void PerformancePage::OnFirstButtonClick()
{
    RecordQuery(0);
    currentPage = 1;
    UpdateStatus();
}

void PerformancePage::OnLastButtonClick()
{
    RecordQuery((totalPage-1) * PageRecordCount);
    currentPage = totalPage;
    UpdateStatus();
}

void PerformancePage::OnSwitchPageButtonClick()
{
        //得到输入字符串
        QString szText = switchPageLineEdit->text();
        //数字正则表达式
        QRegExp regExp("-?[0-9]*");
        //判断是否为数字
        if(!regExp.exactMatch(szText))
        {
           QMessageBox::information(this, tr("提示"), tr("请输入数字"));
           return;
        }
        //是否为空
        if(szText.isEmpty())
        {
           QMessageBox::information(this, tr("提示"), tr("请输入跳转页面"));
          return;
        }
        //得到页数
        int pageIndex = szText.toInt();
        //判断是否有指定页
        if(pageIndex > totalPage || pageIndex < 1)
        {
          QMessageBox::information(this, tr("提示"), tr("没有指定的页面，请重新输入"));
         return;
        }
        //得到查询起始行号
        int limitIndex = (pageIndex-1) * PageRecordCount;
        //记录查询
        RecordQuery(limitIndex);
        //设置当前页
        currentPage = pageIndex;
        //刷新状态
        UpdateStatus();
}
