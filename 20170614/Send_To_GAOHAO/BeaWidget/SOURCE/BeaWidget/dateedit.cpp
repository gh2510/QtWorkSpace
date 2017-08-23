#include "dateedit.h"
#include <QDate>

DateEdit::DateEdit(QWidget *parent) :
    QWidget(parent)
{
    initVariables();
    initWidgets();
}

DateEdit::~DateEdit()
{
    if(m_label)delete m_label;
    if(m_checkdate)delete m_checkdate;
    if(m_edit)delete m_edit;
    if(calendar)delete calendar;
}
void DateEdit::calcGeo()
{

    m_label->move(SE_LEFT_SPACE,SE_TOP);
    m_edit->move(SE_LEFT_SPACE + m_label->width() + SE_WIDGET_SPACE,SE_TOP);
    m_checkdate->move(width() - SE_EDIT_HEIGHT,SE_TOP);

}

void DateEdit::initWidgets()
{
    m_label=new QLabel(this);
    m_label->setFixedSize(80,SE_EDIT_HEIGHT);
    QPalette pl_title;
    pl_title.setColor(QPalette::WindowText,QColor(3,101,100));
    m_label->setPalette(pl_title);


   m_edit=new QLineEdit(this);
   m_edit->setFixedWidth(100);
   m_edit->setFrame(false);



   m_checkdate=new QPushButton(this);
   m_checkdate->setFixedWidth(SE_EDIT_HEIGHT);
   m_checkdate->setIconSize(QSize(SE_EDIT_HEIGHT,SE_EDIT_HEIGHT-2));
   m_checkdate->setStyleSheet("border:none;");
   m_checkdate->setFocusPolicy(Qt::NoFocus);
   m_checkdate->setIcon(QIcon(":/toolWidget/toolWidget/cl"));


    // setup signal-slot connection
     connect(m_checkdate,SIGNAL(clicked()),this,SLOT(showcalendar()));
     m_bEnter=false;

}
void DateEdit::setdate(const QDate& date_checked)
{

    QDate date=date_checked;
    QString datestr=date.toString("yyyy-MM-dd");
    setText(datestr);
    m_edit->setFocus();

    calendar->close();
}

void DateEdit::showcalendar()
{
    calendar = new CalendarDialog();
    calendar->setMinimumSize(400,150);
    calendar->move(QCursor::pos().x()-218,QCursor::pos().y()+ m_checkdate->height());
    connect(calendar,SIGNAL(checkdate(const QDate&)),this,SLOT(setdate(const QDate&)));
    calendar->show();


}

void DateEdit::initVariables()
{
    setFixedHeight(SE_HEIGHT);
     calendar = NULL; // yangmeng 161021 指针初始化为NULL，防止析构出错
}

/*!
  reimplementing protected functions
*/
void DateEdit::resizeEvent(QResizeEvent *e)
{
    calcGeo();
    QWidget::resizeEvent(e);
}

void DateEdit::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBackground(&painter);
}

void DateEdit::enterEvent(QEvent *e)
{
    m_bEnter = true;
    update();
    QWidget::enterEvent(e);
}

void DateEdit::leaveEvent(QEvent *e)
{
     m_bEnter = false;
    update();
    QWidget::leaveEvent(e);
}

/*!
  painting functions
*/
void DateEdit::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);

    if(m_bEnter)
    {
        painter->setPen(QPen(SE_BG_PEN_COLOR,SE_PEN_WIDTH));
    }else{
        painter->setPen(QPen(SE_BG_PEN_COLOR,1));
    }

    painter->setBrush(SE_BG_BRUSH_COLOR);
    painter->drawRoundedRect(rect(),SE_RECT_RADIUS,SE_RECT_RADIUS);

    painter->restore();
}

/*!
  private slot functions
*/





/*!
  public interfaces
*/
void DateEdit::setText(const QString &str)
{
    m_edit->setText(str);
}

void DateEdit::setLabel(const QString& str)
{
    m_label->setText(str);
}

QString DateEdit::text() const
{
    return m_edit->text();
}

void DateEdit::clear()
{
   m_edit->clear();
}
