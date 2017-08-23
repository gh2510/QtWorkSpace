#include "content_widget.h"

ContentWidget::ContentWidget(QWidget *parent):QWidget(parent)
{
    main_splitter=new QSplitter();
    main_splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    main_splitter->setOrientation(Qt::Horizontal);
    main_splitter->setHandleWidth(1);
    
    this->initLeft();
    this->initRight();
    this->initRightTop();
    this->initRightCenter();
    this->initRightCenterFunction();
    this->initRightBottom();
    
    right_splitter->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    right_splitter->setOrientation(Qt::Vertical);
    right_splitter->setHandleWidth(1);
    
    right_top_widget->setFixedSize(250,130);
    right_center_widget->setFixedSize(250,90);
    right_bottom_widget->setFixedSize(250,30);
    
    right_splitter->addWidget(right_top_widget);
    right_splitter->addWidget(right_center_widget);
    right_splitter->addWidget(right_center_function_widget);
    right_splitter->addWidget(right_bottom_widget);
    
    main_splitter->addWidget(left_widget);
    main_splitter->addWidget(right_splitter);
    
    //forbiden drop
    
    for (int i=0;i<right_splitter->count();i++)
    {
        QSplitterHandle *handle=right_splitter->handle(i);
        handle->setEnabled(false);
    }
    
    for (int i=0;i<main_splitter->count();i++)
    {
        QSplitterHandle *handle=main_splitter->handle(i);
        handle->setEnabled(false);
    }
    
    
    QHBoxLayout * main_layout=new QHBoxLayout();
    main_layout->addWidget(main_splitter);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0,0,0,0);
    
    this->setLayout(main_layout);
    this->translateLanguage();
}

void ContentWidget::initLeft()
{
  left_widget=new QWidget();
  label=new QLabel();
  suggest_label=new QLabel();
  system_label=new QLabel();
  
  power_button=new QPushButton();
  
  left_widget->resize(650,500);
  
  QPixmap label_pixmap(":/contentWidget/contentWidget/computer");
  label->setPixmap(label_pixmap);
  label->setFixedSize((label_pixmap.size()));
  
  QFont suggest_font=suggest_label->font();
  suggest_font.setPointSize(12);
  suggest_font.setBold(true);
  suggest_label->setFont(suggest_font);
  suggest_label->setObjectName("grayLabel");
  
  
  QPixmap pixmap(":/contentWidget/ContentWidget/power");
  power_button->setIcon(pixmap);
  power_button->setIconSize(pixmap.size());
  power_button->setFixedSize(180,70);
  power_button->setObjectName("greenButton");
  
  QFont power_font=power_button->font();
  power_font.setPointSize(16);
  power_button->setFont(power_font);
  
  QVBoxLayout *v_layout=new QVBoxLayout();
  v_layout->addWidget(suggest_label);
  v_layout->addWidget(system_label);
  v_layout->addStretch();
  v_layout->setSpacing(15);
  v_layout->setContentsMargins(0,20,0,0);
  
  QHBoxLayout *h_layout=new QHBoxLayout();
  h_layout->addWidget(label,0,Qt::AlignTop);
  h_layout->addLayout(v_layout);
  h_layout->addStretch();
  h_layout->addSpacing(20);
  h_layout->setContentsMargins(30,20,0,0);
  
  QVBoxLayout *main_layout=new QVBoxLayout();
  main_layout->addLayout(h_layout);
  main_layout->addWidget(power_button,0,Qt::AlignCenter);
  main_layout->addStretch();
  main_layout->addSpacing(0);
  main_layout->setContentsMargins(0,0,0,0);

  left_widget->setLayout(main_layout);
          
}

void ContentWidget::initRight()
{
    right_splitter=new QSplitter();
}

void ContentWidget::initRightTop()
{
    right_top_widget=new QWidget();
    login_button=new QPushButton();

    login_button->setFixedSize(150,60);
    login_button->setObjectName("loginButton");
    QFont login_font=login_button->font();
    login_font.setBold(true);
    login_font.setPointSize(12);
    login_button->setFont(login_font);

    QHBoxLayout *login_layout=new QHBoxLayout();
    login_layout->addWidget(login_button);
    login_layout->addStretch();
    login_layout->setContentsMargins(15,0,0,0);

    QVBoxLayout * main_layout=new QVBoxLayout();
    main_layout->addStretch();
    main_layout->addLayout(login_layout);
    main_layout->addStretch();
    main_layout->addSpacing(5);
    main_layout->setContentsMargins(10,10,10,10);

    connect(login_button,SIGNAL(clicked()),this,SIGNAL(showLoginDialog()));

    right_top_widget->setLayout(main_layout);


}

void ContentWidget::initRightCenter()
{
   right_center_widget =new QWidget();

   QHBoxLayout *h_layout=new QHBoxLayout();

   right_center_widget->setLayout(h_layout);
}

void ContentWidget::initRightCenterFunction()
{
    right_center_function_widget=new QWidget();

}

void ContentWidget::initRightBottom()
{
    right_bottom_widget=new QWidget();
}

void ContentWidget::translateLanguage()
{
    power_button->setText(tr("power"));
    login_button->setText(tr("login"));
}





















