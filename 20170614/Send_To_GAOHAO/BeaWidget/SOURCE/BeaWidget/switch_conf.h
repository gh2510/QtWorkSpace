#ifndef SWITCH_CONF_H
#define SWITCH_CONF_H

#include <QWidget>
#include "switchconf.h"
#include <QScrollArea>
#include <QVBoxLayout>

namespace Ui {
class switch_conf;
}

class switch_conf : public QWidget
{
    Q_OBJECT

public:
    explicit switch_conf(QWidget *parent = 0);
    ~switch_conf();

private:
    switchConf *sconf;
    QScrollArea *scrollArea;
    Ui::switch_conf *ui;
};

#endif // SWITCH_CONF_H
