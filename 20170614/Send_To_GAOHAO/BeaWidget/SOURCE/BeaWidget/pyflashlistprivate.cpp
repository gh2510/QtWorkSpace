#include "pyflashlistprivate.h"
#include "ui_pyflashlistprivate.h"

#include <QDebug>

PYFlashListPrivate::PYFlashListPrivate(int hei,QWidget* parent)
    :QWidget(parent),ui(new Ui::PYFlashListPrivate)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    this->m_item_height=hei;
    initVars();
    initSettings();

    m_selectedIndex = -1;       //监控界面选中交换机变色功能 yangmeng 161021
}

void PYFlashListPrivate::initVars()
{
    m_currIndex = 0;
    m_VisibleItemCnt = 0;
    m_ItemCounter = 0;

    m_bAllJobsDone = false;

    m_RotateTimer = new QTimer(this);
    m_RotateTimer->setInterval(UPDATE_TIMER_INTERVAL);
    connect(m_RotateTimer,SIGNAL(timeout()),this,SLOT(DoRotation()));

    m_ItemCountTimer = new QTimer(this);
    m_ItemCountTimer->setInterval(ITEM_COUNTER_TIMER_INTERVAL);
    connect(m_ItemCountTimer,SIGNAL(timeout()),this,SLOT(UpdateItemCount()));
}

void PYFlashListPrivate::initSettings()
{
    setMouseTracking(this);
}

void PYFlashListPrivate::calcGeo()
{
    m_VisibleItemCnt = height()/m_item_height;
    int InvisibleItemCnt = m_IIVec.count() - m_VisibleItemCnt;

    if(InvisibleItemCnt >= 0)
    {
        emit sig_setMaximum(InvisibleItemCnt);
    }
}

void PYFlashListPrivate::makeupJobs()
{
    int Guard = 0;
    for(int index = m_currIndex; index < m_IIVec.count() ;index++)
    {
        if(Guard++ > m_VisibleItemCnt)
        {
            break;
        }

        if(!m_IIVec.at(index).jobDone())
        {
            if(!m_RotateTimer->isActive())
            {
                m_RotateTimer->start();
                m_ItemCountTimer->start();
                break ;
            }
        }
    }

    // reset items which is before the current index 's angle
    for(int index = 0;index < m_currIndex ; index++)
    {
        m_IIVec[index].resetAngle();
    }

    // reset items which is after the visible item's angle
    if((m_currIndex + m_VisibleItemCnt) < m_IIVec.count())
    {
        for(int index  = (m_currIndex + m_VisibleItemCnt);index < m_IIVec.count();index++)
        {
            m_IIVec[index].resetAngle();
        }
    }
}

void PYFlashListPrivate::wheelUp()
{
    if(--m_currIndex < 0)
    {
        m_currIndex = 0;
    }
    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

void PYFlashListPrivate::wheelDown()
{
    if(++m_currIndex + m_VisibleItemCnt > m_IIVec.count())
    {
        m_currIndex = m_IIVec.count() - m_VisibleItemCnt;
    }
    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

void PYFlashListPrivate::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing);
    drawBg(&painter);
    drawItems(&painter);
    drawHoverRect(&painter);
}

void PYFlashListPrivate::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }

    //监控界面选中交换机变色功能 yangmeng 161021
    //原来的设计是鼠标滑过时变色，现在取消

/*    int ItemCnt = e->pos().y()/m_item_height;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        QPointF topLeft(0,ItemCnt*m_item_height);
        QPointF bottomRight(width(),(ItemCnt+1)*m_item_height);
        m_HoverRect = QRectF(topLeft,bottomRight);
        m_strHoverText = m_IIVec.at(m_currIndex+ItemCnt).getText();
        update();
    }*/
}

void PYFlashListPrivate::mousePressEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }
    int ItemCnt = e->pos().y()/m_item_height;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        m_selectedIndex = m_currIndex + ItemCnt;
        emit sig_itemClicked(m_selectedIndex);
        emit sig_itemClicked(m_IIVec[m_selectedIndex].getText());

        //监控界面选中交换机变色功能 yangmeng 161021
        //鼠标点击某个按键后，保持按键的颜色为选中状态
        QPointF topLeft(0,ItemCnt*m_item_height);
        QPointF bottomRight(width(),(ItemCnt+1)*m_item_height);
        m_HoverRect = QRectF(topLeft,bottomRight);
        m_strHoverText = m_IIVec.at(m_currIndex+ItemCnt).getText();
    }
    update();
}

void PYFlashListPrivate::resizeEvent(QResizeEvent *)
{
    calcGeo();
    makeupJobs();
}

void PYFlashListPrivate::leaveEvent(QEvent *)
{
    //m_HoverRect = QRectF();        //监控界面选中交换机变色功能 yangmeng 161021
    update();
}
void PYFlashListPrivate::showEvent(QShowEvent *)
{
    calcGeo();
}

void PYFlashListPrivate::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
    {
        wheelUp();
    }else{
        wheelDown();
    }
}

void PYFlashListPrivate::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,BG_START_COLOR);
    BgGradient.setColorAt(1.0,BG_END_COLOR);
    painter->setBrush(BgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void PYFlashListPrivate::drawItems(QPainter *painter)
{
    if(m_IIVec.count() == 0)
    {
        return ;
    }

    painter->save();

    int Guard = 0;
    qreal initY = 0;

    //监控界面选中交换机变色功能 yangmeng 161021
    //若初始化后还没点击过按键，则默认将第一个按键设置为选中状态
    if(m_selectedIndex == -1 && m_currIndex == 0)
    {
        QPointF topLeft(0,0);
        QPointF bottomRight(width(),m_item_height);
        m_HoverRect = QRectF(topLeft,bottomRight);
        m_strHoverText = m_IIVec.at(m_currIndex).getText();
    }

    for(int index = m_currIndex;index < m_IIVec.count();index++)
    {
        if(Guard++ > m_VisibleItemCnt)
        {
            break ;
        }

        QPointF topLeft(0,initY);
        QPointF bottomRight(width(),initY + m_item_height);
        QRectF ItemRect(topLeft,bottomRight);

        painter->save();
        QTransform t;
        t.translate(ItemRect.center().x(),ItemRect.center().y());

        t.scale(m_IIVec.at(index).getZoomingFactor(),m_IIVec.at(index).getZoomingFactor());
        painter->setTransform(t);

        QPointF TedTopLeft(-width()/2,-m_item_height/2);
        QPointF TedBottomRight(width()/2,m_item_height/2);
        QRectF TedRect(TedTopLeft,TedBottomRight);

        QLinearGradient ItemGradient(TedRect.topLeft(),TedRect.bottomLeft());
        if(index%2)
        {
            ItemGradient.setColorAt(0.0,ITEM_START_COLOR);
            ItemGradient.setColorAt(1.0,ITEM_END_COLOR);
        }
        else
        {
            ItemGradient.setColorAt(0.0,ITEM_START_COLOR_A);
            ItemGradient.setColorAt(1.0,ITEM_END_COLOR_A);
        }
        painter->setPen(Qt::NoPen);
        painter->setBrush(ItemGradient);
        painter->drawRect(TedRect);

        painter->setPen(NORMAL_TEXT_COLOR);
        painter->drawText(TedRect,m_IIVec.at(index).getText(),Qt::AlignVCenter|Qt::AlignHCenter);
        painter->restore();
        /// increment initY
        initY += m_item_height;
    }
    painter->restore();
}

void PYFlashListPrivate::drawHoverRect(QPainter *painter)
{
    if(m_HoverRect.isEmpty() && !m_bAllJobsDone)
    {
        return ;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient HoverGradient(m_HoverRect.topLeft(),m_HoverRect.bottomLeft());
    HoverGradient.setColorAt(0.0,HOVER_START_COLOR);
    HoverGradient.setColorAt(1.0,HOVER_END_COLOR);
    painter->setBrush(HoverGradient);
    painter->drawRoundedRect(m_HoverRect,RECT_RADIUS,RECT_RADIUS);

    QFont BoldFont;
    BoldFont.setBold(true);
    painter->setFont(BoldFont);

    painter->setPen(HOVER_TEXT_COLOR);
    painter->drawText(m_HoverRect,m_strHoverText,Qt::AlignVCenter|Qt::AlignHCenter);
    painter->restore();
}

void PYFlashListPrivate::DoRotation()
{
    int Guard = 0;
    bool bHasJobUndone = false;
    m_bAllJobsDone = false;
    m_HoverRect = QRectF();

    for(int index = m_currIndex;index < m_IIVec.count()/* && Guard < m_ItemCounter*/ ;index++ )
    {
        if(!m_IIVec.at(index).jobDone())
        {
            bHasJobUndone = true;
            m_IIVec[index].updateZoomingFactor();
        }

        if(Guard++ > m_VisibleItemCnt)
        {
            break;
        }
        update();
    }

    if(!bHasJobUndone)
    {
        m_RotateTimer->stop();
        m_bAllJobsDone = true;
    }

}

void PYFlashListPrivate::UpdateItemCount()
{
    if(++m_ItemCounter > m_VisibleItemCnt)
    {
        if(m_ItemCountTimer->isActive())
        {
            m_ItemCountTimer->stop();
            m_ItemCounter = 0;
        }
    }
}

void PYFlashListPrivate::addItem(const QString &str)
{
    ItemInfo ID(str);
    m_IIVec.push_back(ID);

    if(m_RotateTimer->isActive())
    {
        m_RotateTimer->stop();
    }
    m_RotateTimer->start();
}

void PYFlashListPrivate::clear()
{
    m_currIndex = 0;
    m_VisibleItemCnt = 0;
    m_ItemCounter = 0;

    m_bAllJobsDone = false;
    m_IIVec.clear();
    update();
    calcGeo();
    makeupJobs();
}

void PYFlashListPrivate::render()
{
    update();
}

void PYFlashListPrivate::setCurrentIndex(int curIndex)
{
    if(curIndex == m_currIndex)
    {
        return ;
    }

    m_currIndex = curIndex;

    m_VisibleItemCnt = height()/m_item_height;
    int Guard = 0;
    for(int index = m_currIndex ;index < m_IIVec.count();index++)
    {
        m_IIVec[index].resetZoomingFactor();
        if(Guard++ > m_VisibleItemCnt)
        {
            break ;
        }
    }
    m_RotateTimer->start();
    m_ItemCountTimer->start();
}

void PYFlashListPrivate::setItemHeight(int hei)
{
    this->m_item_height=hei;
}
