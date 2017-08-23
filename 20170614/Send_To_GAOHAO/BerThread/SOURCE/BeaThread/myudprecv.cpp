#include "myudprecv.h"

#include <QDebug>

MyUdpRecv::MyUdpRecv(QObject *parent) :
    QObject(parent)
{
    myudp =NULL;
    myudp = new QUdpSocket();
    myudp->bind(13999);   //建立监听
    connect(myudp, SIGNAL(readyRead()), this, SLOT(recvUDP() ));   //接收准备
}

void MyUdpRecv::recvUDP()
{
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"[1] MyUdpRecv :  deal ths udp comtents"
           <<"\n";
    QByteArray datagram;

    do{
        datagram.resize(myudp->pendingDatagramSize());
        myudp->readDatagram(datagram.data(),datagram.size());
    }while(myudp->hasPendingDatagrams());

    int type;
    QDataStream in(&datagram,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_7);
    in>>type;

    emit emitRecvUdp(type);
}

MyUdpRecv::~MyUdpRecv()
{
    if(myudp)
    {
        delete myudp;
        myudp=NULL;
    }
}
