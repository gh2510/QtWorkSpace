#ifndef TELNET_H
#define TELNET_H

#include <QtNetwork>
#include <QObject>
#include <QWidget>

#define MAX_PARAMTER 3
#define IAC  255
#define WILL 251
#define WONT 252
#define DO   253
#define DONT 254
#define ECHO 1
#define NEGONATION_LENGTH 3
#define MAX_COMMAND 1024
#define MAX_RECEIVE 1024*1024
#define MAX_SEND 1024

#define SERVER_ECHO_ON   1
#define SERVER_ECHO_OFF  0
class Telnet
{


private:
    unsigned char echo_status;
    int telnet_connect;
    QString serverIp;
    int port;


public:
    QTcpSocket *tcpSocket;
    Telnet(QObject *parent,int port=23);
    ~Telnet();
    int connect_server();
    int deal_telnet_protocol(unsigned char * receive_server);
    unsigned char * cs_communicate();
    int send_usrcommond(char *);
    void close_socket();
    int get_connected();
    void set_ip(QString ip);



};

#endif // TELNET_H
