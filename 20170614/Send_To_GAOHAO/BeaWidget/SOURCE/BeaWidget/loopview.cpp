#include "loopview.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include"connection.h"
LoopView::LoopView(QWidget *parent) :
    QWidget(parent)
{
    offset = 0;
    myTimerId = 0;
    init_loop();

}
LoopView:: ~LoopView()
{
    killTimer(myTimerId);
    myTimerId = 0;
}
 void LoopView::addText(const QString &newText)
 {
     m_list_showtext.append(newText);
     if(m_list_showtext.length()==1)
     {

         offset=-rect().height();
         update();
         updateGeometry();
     }
 }

  QString LoopView::getText(int i) const
  {
      if(m_list_showtext.length()!=0)
      {
       return m_list_showtext.at(i);
      }
      else
      {
          return "";
      }
  }



  void LoopView::paintEvent(QPaintEvent * /* event */)
  {
       if(m_list_showtext.length()!=0)
       {
          QPainter painter(this);



          int x = -offset;
          for(int i=0;i<m_list_showtext.length();i++)
          {

              QString myText=m_list_showtext.at(i);
              int textWidth = fontMetrics().width(myText);
              int textHeight=fontMetrics().height();
              int startdraw=(this->width()-textWidth)/2;
              painter.setPen( QColor(0, 255, 255));
              painter.drawText(startdraw, x, textWidth, height(),
                           Qt::AlignTop | Qt::AlignHCenter, myText);
             x-=textHeight*2;
          }
       }

  }

  //实时显示还没有被处理的报警信息
  void LoopView::init_loop()
  {

      m_list_showtext.clear();
      QSqlQuery query("",DBConnection::db);;
      query.prepare("select  name,alarmtype from alarmcurrent where  isdeal='否'");
      query.exec();      
      QString name;
      QString alarmType;
      while(query.next())
      {
           name=query.value(0).toString();
           alarmType=query.value(1).toString();
           addText(name+"--"+alarmType);
      }
      offset=-rect().height();
      update();
      updateGeometry();
      query.finish();
      query.clear();
  }
  void LoopView::showEvent(QShowEvent * /* event */)
  {
     myTimerId = startTimer(80);
  }
  void LoopView::timerEvent(QTimerEvent *event)
  {
      if (event->timerId() == myTimerId) {
          if(m_list_showtext.length()!=0)
          {
              ++offset;
              int up_limit= fontMetrics().height()*2*(m_list_showtext.length()-1);
              if (offset >up_limit)
              {
                    init_loop();
              }
              scroll(0, -1);
          }
          else
         {
            init_loop();
          }
      } else {
          QWidget::timerEvent(event);
      }
  }
  void LoopView::hideEvent(QHideEvent * /* event */)
  {
      killTimer(myTimerId);
      myTimerId = 0;
  }
