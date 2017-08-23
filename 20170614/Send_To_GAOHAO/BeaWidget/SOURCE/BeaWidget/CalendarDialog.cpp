#include "calendar_dialog.h"
#include <QCalendarWidget>
#include <QLocale>
#include <QTextCharFormat>
#include <QVBoxLayout>

CalendarDialog::CalendarDialog(QWidget *parent) :QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);

    calendarWidget=new QCalendarWidget(this);
  //calendarWidget->focusWidget();
    calendarWidget->setLocale(QLocale(QLocale::Chinese,QLocale::China));
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
    calendarWidget->setFocusPolicy( Qt::NoFocus );


   QTextCharFormat format;
   format.setBackground(QColor(178,190,126));
   calendarWidget->setWeekdayTextFormat(Qt::Monday, format);
   calendarWidget->setWeekdayTextFormat(Qt::Tuesday, format);
   calendarWidget->setWeekdayTextFormat(Qt::Wednesday, format);
   calendarWidget->setWeekdayTextFormat(Qt::Thursday, format);
   calendarWidget->setWeekdayTextFormat(Qt::Friday, format);
   calendarWidget->setWeekdayTextFormat(Qt::Saturday, format);
    calendarWidget->setWeekdayTextFormat(Qt::Sunday, format);
   calendarWidget->setStyleSheet("QCalendarWidget QWidget{background-color: rgb(178,190,126);"
                                  "alternate-background-color: rgb(178,190,126);}");
    // //设置格式，颜色自选



   connect(calendarWidget,SIGNAL(clicked(const QDate&)),this,SIGNAL(checkdate(const QDate&)));

   QDate cdate=QDate::currentDate();
   QTextCharFormat format1;
   format1.setBackground(QBrush(QColor(137,157,192)));
   calendarWidget->setGridVisible(true);
   calendarWidget->setDateTextFormat(cdate, format1); //生效配置

   main_layout=new QVBoxLayout();

  main_layout->addWidget(calendarWidget);
  main_layout->setContentsMargins(0,10,10,10);
  setLayout(main_layout);
  setFixedSize(400,250);


}

CalendarDialog::~CalendarDialog()
{

}


void CalendarDialog::paintEvent(QPaintEvent *event)
{

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10,10,this->width()-20,this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillPath(path,QBrush(QColor(17,63,61)));
    QColor color(0,0,0,50);

    for(int i=0;i<10;i++)
    {
        QPainterPath patht;
        patht.setFillRule(Qt::WindingFill);
        path.addRect(10-i,10-i,this->width()-(10-i)*2,this->height()-(10-i)*2);
        color.setAlpha((150-qSqrt(i)*50));
        painter.setPen(color);
        painter.drawPath(path);
    }

}
void CalendarDialog::mousePressEvent(QMouseEvent *event)
{
  QRect rc=rect();
  if(!rc.contains(event->pos()))
  {
      this->close();
  }
}
void CalendarDialog::close_window()
{
   this->close();
}

