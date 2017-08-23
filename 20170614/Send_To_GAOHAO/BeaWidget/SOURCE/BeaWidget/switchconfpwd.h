#ifndef SWITCHCONFPWD_H
#define SWITCHCONFPWD_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QStackedLayout>
#include "Telnet/telnetmanager.h"
#include "labelcombox.h"
#include "labeledit.h"
#include "commonbutton.h"

class switchConfPwd : public QWidget
{
    Q_OBJECT

public:
    explicit switchConfPwd(telnetManager *telm,QWidget *parent = 0);
    ~switchConfPwd();
public slots:
    void login();
    void logout();
private:
    void paintEvent(QPaintEvent *);
    telnetManager *telm;
    LabelEdit *tel_ip ;
     LabelEdit *tel_pass;
     LabelEdit *pass;
     QLabel  *teled_ip;

//     commonButton *pwdChangeFormRightBtn;
     QPushButton *pwdChangeFormRightBtn;
     commonButton *login_out;
     QHBoxLayout *main_layout_logined;
       QVBoxLayout *main_layout ;
       QStackedLayout *stack_layout;
       QHBoxLayout *pwdConfLayout;
       QHBoxLayout *pwdConfLayout1 ;
       QVBoxLayout *pwdChangeLayout ;
       QHBoxLayout *pwdChangeForm ;
       QVBoxLayout *pwdChangeFormLeft ;
       QVBoxLayout *pwdChangeFormRight ;
       QHBoxLayout *pwdChangeFormLeft1 ;
       QHBoxLayout *pwdChangeFormLeft2 ;
       QHBoxLayout *pwdChangeFormLeft3;
        QWidget *main_w1;
        QWidget *main_w2;
        QString logFileName;
};

#endif // SWITCHCONFPWD_H
