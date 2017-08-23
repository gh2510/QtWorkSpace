#ifndef ALARMGRAM_H
#define ALARMGRAM_H

#include <QWidget>
#include "labelcombox.h"
#include "labeledit.h"
#include "dateedit.h"
#include "commonbutton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "alarmgraminfo.h"
class AlarmGram : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmGram(QWidget *parent = 0);
    ~AlarmGram();
   void initWidget();
signals:

   void signal_exportclick();
   void signal_searchpram(QString,QString,QString,QString,QString,QString);
public slots:
   void slot_cancel();
   void slot_searchclick();
private:
    QHBoxLayout *toplayout;
    QHBoxLayout  *bottomlayout;
    QHBoxLayout  *centerlayout;
    QScrollArea *scroll;
    QVBoxLayout  *mainlayout;
    LabelComBox *switch_lc;
    LabelComBox *alarmstate_lc;
    DateEdit    *starttime;
    DateEdit    *endtime;
    LabelComBox *alarmlevel;
    LabelComBox *alarmtype;
    commonButton *search;
    commonButton *exportgram;
    commonButton *cancel;

    AlarmGramInfo  *alarminfo;
};

#endif // ALARMGRAM_H
