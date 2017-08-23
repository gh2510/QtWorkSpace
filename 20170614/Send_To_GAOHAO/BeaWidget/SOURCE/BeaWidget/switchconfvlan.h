#ifndef SWITCHCONFVLAN_H
#define SWITCHCONFVLAN_H

#include <QWidget>
#include <QList>
#include <QCheckBox>
#include "labelcombox.h"
#include "labeledit.h"

#include "Telnet/telnetmanager.h"


class switchConfVlan : public QWidget
{
    Q_OBJECT

public:
    explicit switchConfVlan(telnetManager *telm,QWidget *parent = 0);
    ~switchConfVlan();

public slots:
   void checkbox_click(QString);
   void save_check();
private:
    void paintEvent(QPaintEvent *);
    telnetManager *telm;
//    LabelComBox *switchSel;
    LabelEdit *vlanName ;
    LabelEdit *vlanIP;
    QList<int> list_select_port;
    QList<QCheckBox*> list_btn_port;
};

#endif // SWITCHCONFVLAN_H
