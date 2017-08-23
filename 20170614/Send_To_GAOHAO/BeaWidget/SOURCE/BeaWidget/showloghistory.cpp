#include "showloghistory.h"
#include "mainwindow.h"
#include "ui_showloghistory.h"

showLogHistory::showLogHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showLogHistory)
{
    ui->setupUi(this);
    //palette.setColor(QPalette::Window, QColor(26,28,26));  //background color
    //palette.setColor(QPalette::WindowText,QColor("white"));

    this->setPalette(palette);
    mainLayout=new QVBoxLayout(this);
    searchCon1 = new QHBoxLayout();
    showLog=new QTextBrowser(this);
    this->setFixedSize(QApplication::desktop()->width()*6/7,QApplication::desktop()->height()*6/7);     //yangmeng 161031 调整界面布局

    init_search();   //init 界面
    connect(query,SIGNAL(click()),this,SLOT(search()));
    connect(clearTime,SIGNAL(click()),this,SLOT(clearDate()));
}

showLogHistory::~showLogHistory()
{
    delete ui;
    if(searchCon1)delete searchCon1;
    if(showLog)delete showLog;
    if(mainLayout)delete mainLayout;
}

void showLogHistory::init_search()
{
    setWindowTitle(tr("日志查询"));
    starttime = new DateEdit();
    starttime->setFocusPolicy( Qt::NoFocus );
    starttime->setLabel("日志日期 :");

    query = new commonButton();
    query->setText("查询");
    query->setFocusPolicy( Qt::NoFocus );
    query->setFixedSize(110,30);

    clearTime = new commonButton();
    clearTime->setText("清空日期");
    clearTime->setFocusPolicy( Qt::NoFocus );
    clearTime->setFixedSize(110,30);

    searchCon1->addStretch(2);
    searchCon1->addWidget(starttime);
    searchCon1->addStretch(1);
    searchCon1->addWidget(clearTime);
    searchCon1->addStretch(1);
    searchCon1->addWidget(query);
    searchCon1->addStretch(2);

   // searchCon1->setContentsMargins(0,0,0);
    mainLayout->addLayout(searchCon1);
    mainLayout->addWidget(showLog);
}

void showLogHistory::search()
{
    QString date_st=starttime->text();    //get the date need to be searched
    //showLog->clear();   //refresh the log area

    //本日日志文件的名称，此时名称还不含序号信息
   //QString startTime = starttime.toString("yyyyMMdd");
   int i ;
   QFile file;

   for(i=0;i<MainWindow::logFileNumb; i++) {
       logFile=MainWindow::logPath+QString::number(i)+"_"+ date_st +  "_log.txt";
        qDebug()<<"look for: i="<< i << "   FileName =  "<<logFile;
       file.setFileName(logFile);
        if (file.exists()) { break; }
   }
   if (i==MainWindow::logFileNumb ) {  //没有找到当前的日志文件
       return;
       }

    file.setFileName(logFile);
    showLog->clear();

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this,tr("错误"),tr("日志文件打开失败"),QMessageBox::Ok);
        return;
    }
    QTextStream in(&file);
    QString temp;
    while(!in.atEnd())
    {
        temp=in.readLine();
        showLog->append(temp);
    }
}

//清空时间按钮的操作
void showLogHistory::clearDate()
{
    starttime->m_edit->clear();
}
