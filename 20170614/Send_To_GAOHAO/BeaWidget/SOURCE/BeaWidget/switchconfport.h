#ifndef SWITCHCONFPORT_H
#define SWITCHCONFPORT_H

#include <QWidget>
#include "labelcombox.h"
#include "labeledit.h"
#include "commonbutton.h"
#include "Telnet/telnetmanager.h"


class switchConfPort : public QWidget
{
    Q_OBJECT

public:
    explicit switchConfPort(telnetManager *telm,QWidget *parent = 0);
    ~switchConfPort();
public slots:
    void save_port();

private:
    void paintEvent(QPaintEvent *);
    telnetManager *telm;
    LabelComBox *portSelect;
    LabelComBox *portStatus ;
    LabelComBox *portModel;
    LabelComBox *portSpeed ;
    QVBoxLayout *main_layout ;
    QHBoxLayout *portConfLayout ;
    QVBoxLayout *portConfPara;
    QVBoxLayout *portConfSubBtn ;
    QHBoxLayout *portConfLayout1 ;
    QHBoxLayout *portConfLayoutSwitch ;
    QHBoxLayout *portConfLayout2 ;
    QHBoxLayout *portConfLayout3;
    QHBoxLayout *portConfLayout4 ;
    QHBoxLayout *portConfLayout5 ;
    commonButton *portConfPushBtn ;
    QLabel *portConf ;
};

#endif // SWITCHCONFPORT_H
