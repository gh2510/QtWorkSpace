#ifndef CALENDAR_DIALOG_H
#define CALENDAR_DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>
#include<QVBoxLayout>
#include <QCalendarWidget>
class CalendarDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CalendarDialog(QWidget * parent=0);
    ~CalendarDialog();
public slots:
    void close_window();
 signals:
    void checkdate(const QDate&);
protected:

    virtual void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent *event);
     QVBoxLayout  *main_layout;
     QCalendarWidget * calendarWidget;

};
#endif // CALENDAR_DIALOG_H
