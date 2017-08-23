#include "portperform.h"



PortPerform::PortPerform(QWidget *parent) :
    QWidget(parent)
{
    initWidgets();
    initVariables();
}
void PortPerform::calcGeo()
{
    int div=SE_LEFT_SPACE;
    m_portnum->move(div,SE_TOP);
    div+=m_portnum->width()+SE_WIDGET_SPACE;
    m_portip->move(div,SE_TOP);
    div+=m_portip->width()+ SE_WIDGET_SPACE;
    m_portstate->move(div,SE_TOP);
    div+=m_portstate->width()+ SE_WIDGET_SPACE;
    m_portspeed->move(div,SE_TOP);

}

void PortPerform::initWidgets()
{


    m_portnum=new QLabel(this);
    m_portnum->setFixedSize(40,SE_EDIT_HEIGHT);
    m_portnum->setText("1111");
//    QPalette pl_title;
//    pl_title.setColor(QPalette::WindowText,QColor(3,101,100));
//    m_label->setPalette(pl_title);
    m_portip=new QLabel(this);
    m_portip->setFixedSize(100,SE_EDIT_HEIGHT);
    m_portip->setText("1111");

    m_portstate=new QLabel(this);
    m_portstate->setFixedSize(60,SE_EDIT_HEIGHT);
     m_portstate->setText("1111");

    m_portspeed=new QLabel(this);
    m_portspeed->setFixedSize(60,SE_EDIT_HEIGHT);
   m_portspeed->setText("1111");

   //m_edit->setFrame(false);
   //m_edit->setDisabled(true);


}

void PortPerform::initVariables()
{


    setFixedHeight(SE_HEIGHT);
}

/*!
  reimplementing protected functions
*/
void PortPerform::resizeEvent(QResizeEvent *e)
{
    calcGeo();
    QWidget::resizeEvent(e);
}

void PortPerform::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBackground(&painter);
}

void PortPerform::enterEvent(QEvent *e)
{

    update();
    QWidget::enterEvent(e);
}

void PortPerform::leaveEvent(QEvent *e)
{

    update();
    QWidget::leaveEvent(e);
}

/*!
  painting functions
*/
void PortPerform::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);


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
void PortPerform::addItem(const QString &str)
{
    //m_comb->addItem(str);
}

void PortPerform::setLabel(const QString& str)
{
   // m_label->setText(str);
}

QString PortPerform::text() const
{
    //return m_comb->currentText();
}

void PortPerform::clear()
{
  // m_comb->clear();
}
