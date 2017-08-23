#include "switchconf.h"
#include "ui_switchConf.h"
#include <QVBoxLayout>
#include <QDebug>

switchConf::switchConf(QWidget *parent) :
    QWidget(parent),ui(new Ui::switchConf)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->tabWidget->setFixedSize(this->width(),this->height());

    //query_conf = new switchConfQuery(telm);

    query_conf=NULL;
    tabWidget = NULL;
    telm = new telnetManager();
    pwd_conf = new switchConfPwd(telm);

    ui->tabWidget->setFocusPolicy(Qt::NoFocus);
    ui->tabWidget->setDocumentMode(true);
    ui->tabWidget->addTab(pwd_conf,"Telnet登录");
}

switchConf::~switchConf()
{
    if(pwd_conf)delete pwd_conf;
    if(query_conf)delete query_conf;
    if(tabWidget)delete tabWidget;
    telm->close_telnet();
}
