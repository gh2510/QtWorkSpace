#ifndef SWITCHCONF_H
#define SWITCHCONF_H
#include <QWidget>
#include <QTabWidget>
#include "switchconfport.h"
#include "switchconfpwd.h"
#include "switchconfquery.h"
#include "switchconfvlan.h"
#include "Telnet/telnetmanager.h"

namespace Ui {
class switchConf;
}

class switchConf : public QWidget
{
    Q_OBJECT

public:
    explicit switchConf(QWidget *parent = 0);
    ~switchConf();

private:

    switchConfPwd *pwd_conf;
    switchConfQuery *query_conf;
    QVBoxLayout *main_layout ;
    QTabWidget *tabWidget;
    telnetManager *telm;
    Ui::switchConf *ui;
};

#endif // SWITCHCONF_H
