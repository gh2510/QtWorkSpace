#include "labelcombox.h"

LabelComBox::LabelComBox(QWidget *parent) :
    QWidget(parent)
{
    initWidgets();
    initVariables();
}

LabelComBox::~LabelComBox()
{
    if(m_label)delete m_label;
    if(m_comb)delete m_comb;
}
void LabelComBox::calcGeo()
{

    m_label->move(SE_LEFT_SPACE,SE_TOP);
    m_comb->move(SE_LEFT_SPACE + m_label->width() + SE_WIDGET_SPACE,SE_TOP);
    m_comb->setFixedWidth(rect().width()-m_label->width()-20);

}

void LabelComBox::initWidgets()
{
    m_label=new QLabel(this);
    m_label->setFixedSize(100,SE_EDIT_HEIGHT);
    QPalette pl_title;
    pl_title.setColor(QPalette::WindowText,QColor(3,101,100));
    m_label->setPalette(pl_title);


   m_comb=new QComboBox(this);
   m_comb->setFixedWidth(rect().width()-m_label->width()-20);
   m_comb->setStyleSheet("QComboBox {"
                         "border: 1px solid gray; "
                         "border-radius: 3px; "
                         "padding: 1px 2px 1px 2px; "
                        " min-width: 9em; "
                         "background-color:#afdfe4;} "
                        " QComboBox:hover{background-color:rgb(12,92,104); color: white;}"
                         "QComboBox:!editable{ background-color: #afdfe4; color:black;}");
   connect(m_comb,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(indexChanged(QString)));
}



void LabelComBox::initVariables()
{


    setFixedHeight(SE_HEIGHT);
}

/*!
  reimplementing protected functions
*/
void LabelComBox::resizeEvent(QResizeEvent *e)
{
    calcGeo();
    QWidget::resizeEvent(e);
}

void LabelComBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBackground(&painter);
}

void LabelComBox::enterEvent(QEvent *e)
{

    update();
    QWidget::enterEvent(e);
}

void LabelComBox::leaveEvent(QEvent *e)
{

    update();
    QWidget::leaveEvent(e);
}

/*!
  painting functions
*/
void LabelComBox::drawBackground(QPainter *painter)
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
void LabelComBox::addItem(const QString &str)
{
    m_comb->addItem(str);
}

void LabelComBox::setLabel(const QString& str)
{
    m_label->setText(str);
}

void LabelComBox::setIndex(int index)
{
    m_comb->setCurrentIndex(index);
}

QString LabelComBox::text() const
{
    return m_comb->currentText();
}

void LabelComBox::clear()
{
   m_comb->clear();
}
