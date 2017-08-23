#ifndef NEWCAPTURDIALOG_H
#define NEWCAPTURDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include"capturethread.h"

#include <QUdpSocket>

namespace Ui {
class NewCapturDialog;
}

class NewCapturDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCapturDialog(QWidget *parent = 0);
    ~NewCapturDialog();

public slots:
    void slot_start();
    void slot_stop();
    void slot_close();

private:
    Ui::NewCapturDialog *ui;
    CaptureThread *captureThread,*captureThread1; // gaohao Add 捕获多个镜像口数据

    void sendUDPSocket(int type);
    void getTargetIp();
    QHostAddress capturIp;
    int capturPort;
};

#endif // NEWCAPTURDIALOG_H
