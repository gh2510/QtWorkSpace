#include "addline.h"
#include <QAbstractItemView>
#include <QBoxLayout>
AddLine::AddLine(QStringList unswitchname,QStringList selectswitchname,QWidget *parent) :
    QDialog(parent)
{
       this->unswitchnamelist=unswitchname;
       this->selectswitchnamelist=selectswitchname;

       lblunselect = new QLabel("未连接");
       lblselect = new QLabel("连接");

       okButton = new QPushButton("确定",this);
       cancelButton = new QPushButton("取消",this);

       btnRight=new PushButtonDIY();
       btnRight->setPicName(QString(":/img/img/right_ship"));

       btnLeft=new PushButtonDIY();
       btnLeft->setPicName(QString(":/img/img/left_ship"));

       unselect_list=new QListWidget();
       unselect_list->setSelectionMode(QAbstractItemView::MultiSelection);
       unselect_list->setFixedSize(200,400);
       select_list =new QListWidget();
       select_list->setSelectionMode(QAbstractItemView::MultiSelection);
       select_list->setFixedSize(200,400);

       for(int i=0;i<this->unswitchnamelist.size();i++)
       {
         unselect_list->addItem(new QListWidgetItem(this->unswitchnamelist.at(i)));
       }
       for(int i=0;i<this->selectswitchnamelist.size();i++)
       {
         select_list->addItem(new QListWidgetItem(this->selectswitchnamelist.at(i)));
       }

       left_layout=new QVBoxLayout();
       left_layout->addStretch(1);
       left_layout->addWidget(lblunselect,0,Qt::AlignHCenter|Qt::AlignTop);
       left_layout->addStretch(2);
       left_layout->addWidget(unselect_list,0,Qt::AlignHCenter);
       left_layout->addStretch(3);

       center_layout=new QVBoxLayout();
       center_layout->addStretch(10);
       center_layout->addWidget(btnRight,0,Qt::AlignHCenter);
       center_layout->addStretch(2);
       center_layout->addWidget(btnLeft,0,Qt::AlignHCenter);
       center_layout->addStretch(10);

       right_layout=new QVBoxLayout();
       right_layout->addStretch(1);
       right_layout->addWidget(lblselect,0,Qt::AlignHCenter|Qt::AlignTop);
       right_layout->addStretch(2);
       right_layout->addWidget(select_list,0,Qt::AlignHCenter);
       right_layout->addStretch(3);

       top_layout=new QHBoxLayout();
       right_layout->addStretch();
       top_layout->addLayout(left_layout);
       right_layout->addStretch();
       top_layout->addLayout(center_layout);
       right_layout->addStretch();
       top_layout->addLayout(right_layout);
       right_layout->addStretch();

       buttonLayout = new QHBoxLayout();
       buttonLayout->addStretch ();
       buttonLayout->addWidget(okButton);
       buttonLayout->addStretch ();
       buttonLayout->addWidget(cancelButton);
       buttonLayout->addStretch ();

       main_layout=new QVBoxLayout();
       main_layout->addLayout(top_layout);
       main_layout->addLayout(buttonLayout);
       main_layout->setMargin(10);
       main_layout->setSpacing(20);
       setLayout(main_layout);


       connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
       connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

       connect(btnLeft,SIGNAL(buttonclicked()),this,SLOT(ubselect_left()));
       connect(btnRight,SIGNAL(buttonclicked()),this,SLOT(select_right()));

       QPalette palette;
       palette.setColor(QPalette::Window, QColor(54,54,54));
       palette.setColor(QPalette::WindowText,QColor("white"));
       setPalette(palette);

       setWindowTitle(tr("连接"));
}
AddLine::~AddLine()
{
    if(lblunselect) delete lblunselect;
    if(lblselect) delete lblselect;
    if( btnRight) delete btnRight;
    if( btnLeft) delete btnLeft;

    if(okButton) delete okButton;
    if(cancelButton) delete cancelButton;
    if(left_layout) delete left_layout;
    if(center_layout) delete center_layout;
    if( right_layout) delete right_layout;
    if(top_layout) delete top_layout;
    if(buttonLayout) delete buttonLayout;
    if( main_layout) delete main_layout;
}
void AddLine::select_right()
{
    QList<QListWidgetItem*>items = unselect_list->selectedItems();
    for(int i=0;i<items.size();i++)
    {
        select_list->addItem(new QListWidgetItem(items.at(i)->text()));
        int r = unselect_list->row(items.at(i));
        unselect_list->takeItem(r);

    }
}
void AddLine::ubselect_left()
{
 QList<QListWidgetItem*>items = select_list->selectedItems();
 for(int i=0;i<items.size();i++)
 {
     unselect_list->addItem(new QListWidgetItem(items.at(i)->text()));
     int r = select_list->row(items.at(i));
     select_list->takeItem(r);

 }
}
