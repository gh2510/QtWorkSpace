#include "captureimage.h"
#include <QString>
#include <string>
#include<fstream>
#include<iostream>
#include<QFile>
#include<QDebug>
#include<QDataStream>
#include<QDateTime>

CaptureImage::CaptureImage()
{
    g_iRecvBufSize =RCV_BUF_SIZE;
    whileFlag=true;

    memset(g_acRecvBuf, 0, RCV_BUF_SIZE);
    fileNum=100;
    fileSize=10*1024*8;
    currentNum=0;

    adapterID = 0;      //yangmeng 161030
}

void CaptureImage::setFlag(bool flag)
{
    whileFlag=flag;
}

// gaohao Modify char portName[100] 将镜像口名称作为参数
void CaptureImage::setFile(char portName[100],double num,double size,QString path)
{

    this->fileNum=num;
    this->fileSize=size;
    this-> filePath=path;
    memcpy(g_szIfName,portName,sizeof(portName)+1);
}

//设置网卡id，以区分两个网卡不同的最后记录文件序号
void CaptureImage::setAdapteraID(int id)     //yangmeng 161030
{
    adapterID = id;
}

//设置镜像文件中的识别名称 shangchao add in 2017.06.13
void CaptureImage::setLogFileFlag(char logFlag[100])
{
    memcpy(g_szLogFlag,logFlag,sizeof(logFlag)+1);
}

/* 输出mac地址 */
void CaptureImage::ethdump_showMac(const int iType, const char acHWAddr[])
{
    int i = 0;
    if (0 == iType)
    {
        printf("SMAC=[");
    }
    else
    {
        printf("DMAC=[");
    }
    for(i = 0; i < ETHER_ADDR_LEN - 1; i++)
    {
        printf("%02x:", *((unsigned char *)&(acHWAddr[i])));
    }
    printf("%02x] ", *((unsigned char *)&(acHWAddr[i])));
}

/* 物理网卡混杂模式 */
int CaptureImage::ethdump_setPromisc(const char *pcIfName, int fd, int iFlags)
{
    int iRet = -1;
    struct ifreq stIfr;
    /* 获取接口属性标志位 */   
    strcpy(stIfr.ifr_name, pcIfName);

    iRet = ioctl(fd, SIOCGIFFLAGS, &stIfr);
    if (0 > iRet)
    {
        perror("[Error]Get Interface Flags");
        return -1;
    }

    if (0 == iFlags)
    {
        /* 取消混杂模式*/
        stIfr.ifr_flags &= ~IFF_PROMISC;
    }
    else
    {
        /* 设置混杂模式 */
        stIfr.ifr_flags |= IFF_PROMISC;
    }

    iRet = ioctl(fd, SIOCSIFFLAGS, &stIfr);
    if (0 > iRet)
    {
        perror("[Error]Set Interface Flags");
        return -1;
    }

    return 0;
}


/* Init L2 Socket */
int CaptureImage::ethdump_initSocket()
{
    int iRet = -1;
    int fd = -1;
    struct ifreq stIf;
    struct sockaddr_ll stLocal = {0};

    /* 创建套接字 */
    fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (0 > fd)
    {
        perror("[Error]Initinate L2 raw socket");
        return -1;
    }

     /* 网卡混杂模式 */
    ethdump_setPromisc(g_szIfName, fd, 1);

    /* 设置socket选项 */
    iRet = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &g_iRecvBufSize,sizeof(int));
    if (0 > iRet)
    {
        perror("[Error]Set socket option");
        close(fd);
        return -1;
    }

    /* 获取物理网卡接口索引 */
    strcpy(stIf.ifr_name, g_szIfName);
    iRet = ioctl(fd, SIOCGIFINDEX, &stIf);
    if (0 > iRet)
    {
        perror("[Error]Ioctl operation");
        close(fd);
        return -1;
    }
     qDebug()<< "4.网卡interface index完成"<<endl;
    /* 绑定物理网卡 */
    stLocal.sll_family = PF_PACKET;
    stLocal.sll_ifindex = stIf.ifr_ifindex;
    stLocal.sll_protocol = htons(ETH_P_ALL);
    iRet = bind(fd, (struct sockaddr *)&stLocal, sizeof(stLocal));
    if (0 > iRet)
    {
        perror("[Error]Bind the interface");
        close(fd);
        return -1;
    }

    return fd;
}

/* 解析IP数据包 */
int CaptureImage::ethdump_parseIpHead(const struct ip *pstIpHead)
{
    struct protoent *pstIpProto = NULL;
    if (NULL == pstIpHead)
    {  qDebug()<<"parsel start  "<<endl;
        return -1;
    }
    /* 协议类型、源IP、目的IP*/
    pstIpProto = getprotobynumber(pstIpHead->ip_p);
    if(NULL != pstIpProto)
    {
        printf(" IP-Pkt-Type:%d(%s) ", pstIpHead->ip_p, pstIpProto->p_name);
    }
    else
    {
        printf(" IP-Pkt-Type:%d(%s) ", pstIpHead->ip_p, "None");
    }
    printf("SAddr=[%s] ", inet_ntoa(pstIpHead->ip_src));
    printf("DAddr=[%s] ", inet_ntoa(pstIpHead->ip_dst));
    return 0;
}

/* 捕获网卡数据帧*/
void CaptureImage::ethdump_startCapture(const int fd)
{
    int iRet = -1;
    socklen_t stFromLen = 0;
    printf("开始:捕获网卡数据帧：");
    double currentSize=0;

    //读出记录的当前存储的文件中最新的一个的序号，新文件的保存文件名以此加1，模为文件个数 ---qhy 2016.10.26 update begin
    //文件名的格式为：序号_镜像端口_记录的起始时间.bin    currentNum
    QSqlQuery query("",DBConnection::db);
    QString strAdpID = QString::number(adapterID);               //yangmeng 161030 区分两个网卡不同的最新记录序号

    QString cur_seq = "当前序号"+strAdpID;

    qDebug()<< "当前序号 cur_seq: "<<cur_seq;
    query.prepare("select value from sysdict where attr=? " );
    query.bindValue(0, cur_seq );
    query.exec();
    if(!query.next())
    {
        qDebug()<<"当前序号为空 00000";
        currentNum = 0;
    }
    else
    {
        currentNum = (query.value(0).toInt() + 1)%100 ;     //yangmeng 161030
        qDebug()<<"当前序号为空 111111";
    }

    QString startTime = QDateTime::currentDateTime().toString("yyMMddhhmmss");
    QString fileName=filePath+QString::number(currentNum)+ "_"+ g_szLogFlag + "_" + startTime +".bin";

    //此序号文件如果存在，删除旧的，再写新的
    //yangmeng 161030 加入多网卡判断
    //yangmeng 161101修改文件路径到1T硬盘
    QByteArray temp1=("rm  -f  " + filePath + QString::number(currentNum)+ "_"+g_szLogFlag+"_*.*").toLatin1();

    char *ch1=temp1.data();
    system(ch1);    

    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"文件打开失败"<<endl;
        return;
    }

    qDebug()<<"OpenFileds";

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    //若文件打开成功，则记录当前序号到sysdict中,  2016.10.26 qhy update begin
    query.prepare(" update sysdict set  value = ? where attr= ? " );
    query.bindValue(0, QString::number(currentNum));
    query.bindValue(1, cur_seq );
    query.exec();

    while(whileFlag)
    {
        /* 清空接收缓冲区*/
        memset(g_acRecvBuf, 0, RCV_BUF_SIZE);
        /* 接收数据帧 */

        iRet = recvfrom(fd, g_acRecvBuf, g_iRecvBufSize, 0, NULL, &stFromLen);
        if (0 > iRet)
        {
            printf("no rev\n");
            continue;
        }

        out.writeRawData(g_acRecvBuf,iRet);

        currentSize+=iRet;
        //qDebug()<<"Cur:  "<<  currentSize <<"            fileSize:" <<fileSize  << "        ---" << fileSize -  currentSize << endl;
        if( currentSize >= fileSize)
        {
            file.close();

            currentNum = (currentNum + 1) % fileNum;
            startTime = QDateTime::currentDateTime().toString("yyMMddhhmmss");      //yangmeng 161101 创建新文件时重新获取系统时间
            fileName=filePath+QString::number(currentNum)+ "_"+ g_szLogFlag + "_"+ startTime +".bin";

            //此序号文件如果存在，删除旧的，再写新的     //yangmeng161101 增加双网卡判断 修改文件路径到1T硬盘
            QByteArray temp=("rm  -f " + filePath +QString::number(currentNum)+ "_"+g_szLogFlag+"_*.*").toLatin1();
            query.prepare(" update sysdict set  value = ? where attr= ? " );
            query.bindValue(0, QString::number(currentNum));
            query.bindValue(1, cur_seq );
            query.exec();

            char *ch=temp.data();
            system(ch);

            file.setFileName(fileName);
            if(!file.open(QIODevice::WriteOnly))
            {
                return;
            }
            currentSize=0;
        }
    }
    file.close();
    query.finish();
    query.clear();
}   //2016.10.26 qhy update end

void CaptureImage::run()
{
    int iRet = -1;
    int fd   = -1;

    /* 初始化套接字 */
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"初始化套接字 start up  CaptureImage"
           <<"\n";
    fd = ethdump_initSocket();

    if( fd <0 )
    {
        return ;
    }

    /* 捕获数据包*/
    ethdump_startCapture(fd);

    /* 关闭SOCKET */
    close(fd);
}
