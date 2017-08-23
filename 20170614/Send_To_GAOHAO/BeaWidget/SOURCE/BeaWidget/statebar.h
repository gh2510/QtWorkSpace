#ifndef STATEBAR_H
#define STATEBAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QDateTime>
#include <qmath.h>
#include <QVBoxLayout>
#include <QTimerEvent>
class StateBar : public QWidget
{
    Q_OBJECT
public:
    explicit StateBar(QWidget *parent = 0);
    ~StateBar();
protected:
     virtual void paintEvent(QPaintEvent * event);
     void timerEvent( QTimerEvent *event );


signals:

public slots:
private:
     QVBoxLayout *main_layout;
      int m_nTimerId;
      QLabel *lbl_time;
      QLabel *lbl_startTime;
       QDateTime time;
       QDateTime startTime;
       QTime sTime;
};

#endif // STATEBAR_H
