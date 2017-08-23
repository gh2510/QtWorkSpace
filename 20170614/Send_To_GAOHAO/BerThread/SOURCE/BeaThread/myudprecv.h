#ifndef MYUDPRECV_H
#define MYUDPRECV_H

#include <QObject>
#include <QUdpSocket>

class MyUdpRecv : public QObject
{
    Q_OBJECT
public:
    explicit MyUdpRecv(QObject *parent = 0);
    ~MyUdpRecv();

signals:
    void emitRecvUdp(int);

public slots:
    void recvUDP();

private:
    QUdpSocket *myudp;

};

#endif // MYUDPRECV_H
