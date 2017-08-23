#include "labeledit.h"

LabelEdit::LabelEdit(QWidget *parent) :
    QWidget(parent)
{
    initWidgets();
    initVariables();
}

LabelEdit::~LabelEdit()
{
    if(m_label)delete m_label;
    if(m_edit)delete m_edit;
}
void LabelEdit::calcGeo()
{

    m_label->move(SE_LEFT_SPACE,SE_TOP);
    m_edit->move(SE_LEFT_SPACE + m_label->width() + SE_WIDGET_SPACE,SE_TOP);
    m_edit->setFixedWidth(rect().width()-m_label->width()-5);

}

void LabelEdit::initWidgets()
{
    m_label=new QLabel(this);
    m_label->setMaximumSize(60,SE_EDIT_HEIGHT);
    //m_label->setFixedSize(60,SE_EDIT_HEIGHT);
    QPalette pl_title;
    pl_title.setColor(QPalette::WindowText,QColor(3,101,100));
    m_label->setPalette(pl_title);


   m_edit=new QLineEdit(this);
   m_edit->setFixedWidth(rect().width()-m_label->width()-5);
   m_edit->setFrame(false);
   m_edit->setAlignment(Qt::AlignHCenter);
   m_edit->setReadOnly(true);



}
void LabelEdit::setEditDisabled(bool flag)
{
    m_edit->setDisabled(flag);

}

 void LabelEdit::setEditReadOnly(bool flag)
 {
     m_edit->setReadOnly(flag);

 }
void LabelEdit::initVariables()
{
    setFixedHeight(SE_HEIGHT);
}

/*!
  reimplementing protected functions
*/
void LabelEdit::resizeEvent(QResizeEvent *e)
{
    calcGeo();
    QWidget::resizeEvent(e);
}

void LabelEdit::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBackground(&painter);
}

void LabelEdit::enterEvent(QEvent *e)
{

    update();
    QWidget::enterEvent(e);
}

void LabelEdit::leaveEvent(QEvent *e)
{

    update();
    QWidget::leaveEvent(e);
}

/*!
  painting functions
*/
void LabelEdit::drawBackground(QPainter *painter)
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
void LabelEdit::setText(const QString str)
{
    m_edit->setText(str);
}

void LabelEdit::setLabel(const QString& str)
{
    m_label->setText(str);
}

QString LabelEdit::text() const
{
    return m_edit->text();
}

void LabelEdit::clear()
{
   m_edit->clear();
}

void LabelEdit::setLabelWidth(int width){
    m_label->setFixedWidth(width);
}
void LabelEdit::setEditWidth(int width){
    m_edit->setFixedWidth(width);
}


