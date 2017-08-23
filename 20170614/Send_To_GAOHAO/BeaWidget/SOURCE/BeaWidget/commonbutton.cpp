#include "commonbutton.h"
#include <QVBoxLayout>

commonButton::commonButton(QWidget *parent) :
    QWidget(parent)
{

    pushBtn= new QPushButton(this);
    pushBtn->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                           " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                        "border-style: outset;}"
                                       "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                       "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                           " border-style: outset; }"
                           "QPushButton:disabled{color:gray;}");
    pushBtn->setFocusPolicy(Qt::NoFocus);
    pushBtn->setFixedHeight(30);
    main_layout = new QVBoxLayout();
    main_layout->addWidget(pushBtn,0,Qt::AlignVCenter);
    main_layout->setContentsMargins(0,0,0,0);
    this->setLayout(main_layout);

    connect(pushBtn,SIGNAL(clicked()),this,SIGNAL(click()));
}

commonButton::~commonButton()
{
  //  if(pushBtn) delete pushBtn;
 //  if(main_layout) delete main_layout;
}



void commonButton::setWidth(int width){
    pushBtn->setFixedWidth(width);

}

void commonButton::setText(QString text){
    pushBtn->setText(text);
}




