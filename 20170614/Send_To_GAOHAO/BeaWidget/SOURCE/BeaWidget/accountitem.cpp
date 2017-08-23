#include "accountitem.h"
#include "ui_accountitem.h"

AccountItem::AccountItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);

    mouse_press = false;
    mButton=new PushButtonDIY();
    m_lbldel=new QLabel();

    QPixmap pixmap(":/img/img/Image_users.png");

    m_lbldel->setPixmap(pixmap);
    m_lbldel->setFixedSize(QSize(50,50));


    initView();

}
AccountItem::AccountItem( const QString& name, QWidget *parent /*= 0*/ )
    : QWidget(parent)
{
    ui->setupUi(this);

    m_lbldel=new QLabel();
    mouse_press = false;
    mButton=new PushButtonDIY();
    mButton->setText(name);
    QPixmap pixmap(":/img/img/Image_users.png");
    m_lbldel->setPixmap(pixmap);
    m_lbldel->setFixedSize(QSize(50,50));
    initView();
}

void AccountItem::initView()
{
    main_layout=new QHBoxLayout();
    main_layout->addWidget(m_lbldel,Qt::AlignVCenter);
    main_layout->addStretch();
    main_layout->addWidget(mButton,Qt::AlignVCenter);
    main_layout->addStretch();
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);
    setFixedHeight(60);
}

void AccountItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
    }
}



void AccountItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_press) {
        emit sigShowAccount(mButton->text());
        mouse_press = false;
    }
}

void AccountItem::SetNickName( const QString& name )
{
     mButton->setText(name);
}

QString AccountItem::GetNickName() const
{
    return mButton->text();
}
AccountItem::~AccountItem()
{
    if(main_layout) delete main_layout;
    if(mButton) delete mButton;
    if(m_lbldel) delete m_lbldel;
    delete ui;
}
