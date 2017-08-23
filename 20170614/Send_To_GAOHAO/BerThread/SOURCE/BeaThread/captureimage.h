#ifndef CAPTUREIMAGE_H
#define CAPTUREIMAGE_H
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<netpacket/packet.h>
#include<net/ethernet.h>
#include<net/if.h>
#include<arpa/inet.h>
#include<errno.h>
#include<QString>
#include<QDebug>
#include <QSqlQuery>
#include"connection.h"
#include "qobject.h"
#include <QVariant>

/*接收缓冲区大小*/
#define RCV_BUF_SIZE  1024*5
 using namespace std;

class CaptureImage
{
private:
    /*接收缓冲区*/

    char g_szIfName[100];
    int g_iRecvBufSize;
    char g_acRecvBuf[RCV_BUF_SIZE];
    /*物理网卡*/

    int adapterID;          //yangmeng 161030
    char g_szLogFlag[100];  //shangchao 170613

public:
    CaptureImage();

    QString filePath;
    long fileNum;
    long fileSize;
    bool whileFlag;
    long currentNum;
    int file_num;
    void setFlag(bool flag);
    void setFile(char portName[],double num,double size, QString path); // gaohao Add portName
    void ethdump_showMac(const int iType, const char acHWAddr[]) ;
    int ethdump_setPromisc(const char *pcIfName, int fd, int iFlags);
    int ethdump_initSocket();
    int ethdump_parseIpHead(const struct ip *pstIpHead);
    void ethdump_startCapture(const int fd);
    void run();

    void setAdapteraID(int id);     //yangmeng 161030
    void setLogFileFlag(char logFlag[]);
};

#endif // CAPTUREIMAGE_H
