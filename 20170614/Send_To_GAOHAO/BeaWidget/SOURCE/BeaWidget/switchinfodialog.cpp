#include "switchinfodialog.h"
#include "ui_switchinfodialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSqlQuery>
#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
SwitchInfoDialog::SwitchInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SwitchInfoDialog)
{
    ui->setupUi(this);
    setFixedSize(QApplication::desktop()->width()*3/5,
                 QApplication::desktop()->height()*3/5);
    portNum=0;

    for(int i=0;i<60;i++)
    {
        state.append("在线");
    }

    switchTableModel = new myStandardItemModel();

    ui->tableview->setModel(switchTableModel);
    ui->tableview->sortByColumn (0,Qt::AscendingOrder);
    ui->tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableview->horizontalHeader()->setStretchLastSection(true);
    ui->tableview->verticalHeader ()->setVisible (false);
    ui->tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableview->setSelectionMode(QAbstractItemView::SingleSelection);

//    ui->tableview->setFixedHeight(this->height()*4/5);
    ui->tableview->setAutoFillBackground (true);
    ui->tableview->verticalHeader()->setDefaultSectionSize(40);

    connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(slot_close()));

    setWindowTitle(tr("交换机详细信息"));
//    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    setWindowFlags(Qt::Tool|Qt::WindowCloseButtonHint);
}

void SwitchInfoDialog::init_table()
{
    switchTableModel->clear();
    switchTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("端口号")));
    switchTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("设备信息")));
    switchTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("在线状态")));

    ui->tableview->setModel(switchTableModel);
    ui->tableview->setColumnWidth(0,120);       //yangmeng 161026 修改布局
    ui->tableview->setColumnWidth(1,240);
//    ui->tableview->setFixedWidth(600);
   // QFile file(nameL->text().trimmed().right(2)+".xml");

    QFile file(fileName.right(2)+".xml");
    qDebug()<<"SwitchInfoDialog::init_table(): "<<fileName<<endl;;
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(0," 错误","打开配置文件失败",QMessageBox::Ok);
        return;
    }
    QDomDocument domDocument;
    QString errorMsg="no error";
    int errorLine=0;
    int errorColumn=0;
    if(!domDocument.setContent(&file,&errorMsg,&errorLine,&errorColumn))
    {
            QMessageBox::information(0,"读取配置文件失败",tr(" 第%1行，第%2列：\n%3").arg(errorLine).arg(errorColumn).arg(errorMsg),QMessageBox::Ok);
         return;
    }
    QDomElement root = domDocument.documentElement();
    if(root.tagName()=="Switch")
    {
        QDomNode node=root.firstChild();//port
        QDomElement element=node.firstChildElement();
        int itemCount=0;
        while(portNum>itemCount)
        {

            switchTableModel->setItem(itemCount,0,new QStandardItem(element.text()));
            element=element.nextSiblingElement();
            switchTableModel->setItem(itemCount,1,new QStandardItem(element.text()));
            switchTableModel->setItem(itemCount,2,new QStandardItem(state.at(itemCount)));
            node=node.nextSibling();
            element=node.firstChildElement();
            itemCount++;

        }
    }

    file.close();
    return;

}

void SwitchInfoDialog::setSwitch(QString name, QString location ,QString num)
{
    ui->nameL->setText(name);
    fileName=name;
    ui->locationL->setText(location);
    portNum=num.toInt();
}

void SwitchInfoDialog::setList(QStringList list)
{
    state=list;
}

SwitchInfoDialog::~SwitchInfoDialog()
{
    delete ui;
}

void SwitchInfoDialog::slot_close()
{
//    this->close();
    this->hide();

}
