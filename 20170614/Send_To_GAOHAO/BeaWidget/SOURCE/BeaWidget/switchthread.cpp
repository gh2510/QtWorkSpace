#include "switchthread.h"
#include"connection.h"
#include "time.h"
#include<QDateTime>
#include "sigle_topo_info.h"

double SwitchThread::temMaxValue = 100;
double SwitchThread::memMaxValue = 100;
double SwitchThread::tmp_in = 500;
double SwitchThread::tmp_out = 500;
double SwitchThread::ele_in = 400;
double SwitchThread::ele_out = 400;
double SwitchThread::fiber_in = 500;
double SwitchThread::fiber_out = 500;
SwitchThread::SwitchThread(QObject *parent,QString name)
    : QThread(parent)
{
    switch_name=name;
    error=0;
    th_stop=false;//
    reached=true;

    sqlquery = new QSqlQuery("",DBConnection::db);
    //从数据库中查得交换机的ip和团体
    sqlquery->prepare(" select IP, IP2, community, remark from switch where name= ?");
    sqlquery->bindValue(0,switch_name);
    sqlquery->exec();
     sqlquery->next();
    this->ipaddress =  sqlquery->value (0).toString (); // QVariant
    this->backupAddr =  sqlquery->value(1).toString();
    this->mycommunity= sqlquery->value (2).toString ();
//     qDebug()<<"mycommunity "<<mycommunity;
//     qDebug()<<"mycommunity "<<ipaddress;
//     qDebug()<<"mycommunity "<<backupAddr;
   // mycommunity="public";
    this->type =  sqlquery->value(3).toString();

     int cnt = type.toInt()*2;
    int j;
    for(int i= 0; i< cnt; i++) // 获得特定端口的阈值
    {
        j=i/2;
       // 对于交换机端口，需要判断是否有特殊设定---qhy
        QString ls_sql = "select  value from  singlethresh where switchname =? and switchport=? and type =?";
        sqlquery->prepare(ls_sql);
        sqlquery->bindValue(0,switch_name);
        sqlquery->bindValue(1,QString::number(j+1));
        sqlquery->bindValue(2,"进速率");
        sqlquery->exec();
        // 如果数据库中存在，则记录到内存中
        if ( sqlquery->next()) {
             double temp = sqlquery->value(0).toDouble();
             switchInSignalValue.insert(j+1,temp);
        }

         sqlquery->prepare(ls_sql);
        sqlquery->bindValue(0,switch_name);
         sqlquery->bindValue(1,QString::number(j+1));
         sqlquery->bindValue(2,"出速率");
         sqlquery->exec();
        if ( sqlquery->next()) {
            double temp =  sqlquery->value(0).toDouble();
            switchOutSignalValue.insert(j+1,temp);
          //  qDebug()<< "switch_name:" << switch_name << "port " << j+1 << "     tmp_out :" << tmp_out << endl;
           }
        sqlquery->finish();
        //sqlquery->clear();
    }
 }

// gaohao Add 初始化交换机共用的阈值信息
void SwitchThread::InitSwitchComInfo()
{
    //QSqlQuery query("",DBConnection::db);
    // gaohao 设定各阈值初始值 并从数据库中获取
    QSqlQuery query("",DBConnection::db);
    temMaxValue = 100;
    memMaxValue = 100;
    tmp_in = 500;
    tmp_out = 500;
    query.exec("select * from thresh where alarmname='温度（°C）'");
    query.next();
    temMaxValue=query.value(1).toInt();

    query.exec("select * from thresh where alarmname='内存利用率（%）'");
    query.next();
    memMaxValue=query.value(1).toInt();

    //默认阈值分为电口进，电口出，光口进，光口出 四种类型---qhy,2016.10.26
   query.exec("select * from thresh where alarmname='电口(千兆)端口进速率（Mbps）'");
    query.next();
    ele_in=query.value(1).toDouble();
    query.exec("select * from thresh where alarmname='电口(千兆)端口出速率（Mbps）'");
    query.next();
    ele_out=query.value(1).toDouble();
    query.exec("select * from thresh where alarmname='光口(万兆)端口进速率（Mbps）'");
    query.next();
    fiber_in=query.value(1).toDouble();
    query.exec("select * from thresh where alarmname='光口(万兆)端口出速率（Mbps）'");
    query.next();
    fiber_out=query.value(1).toDouble();
    //qDebug()<<"thresh:"<< ele_out << "  "<<fiber_out<<endl;
    query.finish();
    query.clear();
}

SwitchThread::~SwitchThread()
{
   sqlquery->finish();
   sqlquery->clear();
}
void SwitchThread::run ()
{
    enum {IP, IP2} curStatus = IP;
    int IP1Down = 0, IP2Down = 0;

    while(!th_stop)
    {
        if(curStatus == IP)
        {
          // emit sig_setNormal(switch_name);//交换机重新设置为正常
            snmpQuery(ipaddress);
            IP1Down = time(NULL);
            curStatus = IP2;
        }
        else if(curStatus == IP2)
        {
            //emit sig_setNormal(switch_name);//交换机重新设置为正常
            if(switch_name == "H1" || switch_name == "H2")      //只有核心交换机才有带外管理 yangmeng 161028
            {
                snmpQuery(backupAddr);
            }
            IP2Down = time(NULL);
            curStatus = IP;
        }
        if(IP1Down && IP2Down && abs(IP1Down - IP2Down) < 10)
        {
            emit sig_warning(switch_name,"交换机不可达", "X");//认为交换机不可达,--qhy
            for(int i=0;i<this->type.toInt(); i++)//  读取端口状态
            {
               // qDebug()<<"DownSign";
                emit sig_portStatus(switch_name,i,2);
            }
           reached=false;
            msleep(10000);
            IP1Down = IP2Down = 0;

        }
    }
}

// yangmengo 161101 Add 添加信号槽 用于接收阈值新增信息 新增阈值时发送 分别时交换机名称 端口号 输入输出属性（0为输入 1为输出） 阈值信息
void SwitchThread::alarmAdd(QString switchName, int port , int inout, double value)
{
    if(switch_name == switchName)
    {
         if(inout == 0) // 输入
        {
            switchInSignalValue.insert(port,value);
            qDebug()<<"添加阈值-输入"<<port<<"----"<<value;
        }
        else if(inout == 1) // 输出
        {
            switchOutSignalValue.insert(port,value);
            qDebug()<<"添加阈值-输出"<<port<<"----"<<value;
        }

    }
}


// goahao Add 添加信号槽 用于接收阈值更改信息 修改阈值时发送 分别时交换机名称 端口号 输入输出属性（0为输入 1为输出） 阈值信息
void SwitchThread::alarmSet(QString switchName, int port , int inout, double value)
{

    if(switch_name == switchName)
    {
         if(inout == 0) // 输入
        {
            QMap<int,double>::iterator itor1;
            for ( itor1 = switchInSignalValue.begin(); itor1 != switchInSignalValue.end(); ++itor1 ) {
                if(itor1.key() ==port)
                {
                    switchInSignalValue[port] = value;
                    qDebug()<<"修改阈值-输入"<<port<<"----"<<value;
                    break;
                }
            }
        }
        else if(inout == 1) // 输出
        {
            QMap<int,double>::iterator itor1;
            for ( itor1 = switchOutSignalValue.begin(); itor1 != switchOutSignalValue.end(); ++itor1 ) {
                if(itor1.key() ==port)
                {
                    switchOutSignalValue[port] = value;
                    qDebug()<<"修改阈值-输出"<<port<<"----"<<value;
                    break;
                }
            }
        }

    }
}

// gaohao Add 删除特定阈值时发送 分别时交换机名称 端口号 输入输出属性（0为输入 1为输出的
void SwitchThread::alarmDel(QString switchName, int port , int inout)
{
    if(switch_name == switchName)
    {
        if(inout == 0) // 输入
        {
            QMap<int,double>::iterator itor1;
            for ( itor1 = switchInSignalValue.begin(); itor1 != switchInSignalValue.end(); ++itor1 ) {
                if(itor1.key() ==port)
                {
                    switchInSignalValue.remove(port);
                    break;
                }
            }
        }
        else if(inout == 1) // 输出
        {
            QMap<int,double>::iterator itor1;
            for ( itor1 = switchOutSignalValue.begin(); itor1 != switchOutSignalValue.end(); ++itor1 ) {
                if(itor1.key() ==port)
                {
                    switchOutSignalValue.remove(port);
                    break;
                }
            }
        }

    }
}

void SwitchThread::snmpQuery(QString ip)
{

//    qDebug()<<"****************"<<ip<<"***************";
    if(ip.size() == 0)
    {
        return;
    }
    Snmp::socket_startup();  // Initialize socket subsystem
    //---------[ make a GenAddress ]------------------------------------------
    UdpAddress address;// make a SNMP++ Generic address
//    address=ip.toLocal8Bit ()+":161";   //Shang 2017.03.02  取消注释
    address = ip.toLocal8Bit ()+":4700";
    //---------[ determine options to use ]-----------------------------------
    snmp_version version=version2c;                  // default is v1
    int retries=3;                                  // default retries is 1
    int timeout=20;                                // default is 100ms
//    u_short port=161;                               // default snmp port is 161
    u_short port=4700;
    OctetStr community;
    community=mycommunity.toLocal8Bit ();// community name

    //----------[ create a SNMP++ session ]-----------------------------------
    int status;
    // bind to any port and use IPv6 if needed
    Snmp snmp(status, 0, (address.get_ip_version() == Address::version_ipv6));

    if ( status != SNMP_CLASS_SUCCESS) {
        qDebug() << "SNMP++ Session Create Fail, " << snmp.error_msg(status) << "\n";
    }

    //从配置文件中读取OId的值
    QDomDocument document;
    QString filename = "oid"+this->type+".xml";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
            qDebug()<<"无法打开配置文件";
            return;
     }
     else
     {
//            qDebug()<<"打开配置文件成功";
            if(!document.setContent(&file))
            {
                qDebug()<<"加载文件失败";
                return;
            }
            file.close();
      }
    QDomElement root=document.documentElement();

    QDomNodeList list;
    if(root.tagName()=="Oid")
    {
        list=root.childNodes();
    }
    else
    {
        qDebug() << "Wrong oid file";

    }
    //--------[ build up SNMP++ object needed ]-------------------------------
    Vb vb[list.size()];                                 // construct a Vb object
    Oid oid[list.size()];
    QMap<Oid, QString> oidMap;
    //---------[ make Oid object to retrieve ]------------------------------
    for(int i=0;i<list.size();i++)
    {

        oid[i]=qPrintable(list.at(i).toElement().text());// oid[i]=list.at(i).toElement().toText();
        oidMap.insert(oid[i], list.at(i).toElement().tagName());
        //qDebug()<<"oid"<<list.at(i).toElement().text()<<endl;
    }
    for (int i=0;i<list.size();i++)
    {
        vb[i].set_oid(oid[i]);                       // set the Oid portion of the Vb
    }


    address.set_port(port);
    CTarget ctarget( address);             // make a target using the address

    ctarget.set_version( version);         // set the SNMP version SNMPV1 or V2
    ctarget.set_retry( retries);           // set the number of auto retries
    ctarget.set_timeout( timeout);         // set timeout
    ctarget.set_readcommunity( community ); // set the read community name


    //-------[ issue the request, blocked mode ]-----------------------------
    SnmpTarget *target;
    target = &ctarget;

    double cpuusage;
    double memusage;
    //double lastOut[60]={-1};
    //double lastIn[60]={-1};
    qlonglong lastOut[60]={-1};
    qlonglong lastIn[60]={-1};
    double inSpeed;
    double outSpeed;
    //double value[183]={0};
    qlonglong value[183]={0};
    double time_start;
    double time_end;

    qlonglong inDiff[60]={0};//oid 改变之后数据类型uint32改掉
    qlonglong outDiff[60]={0};

    int inDiffZeroCnt[60];      //yangmeng 161025 记录流量差值持续为0的次数
    int outDiffZeroCnt[60];

   // bool first[60]={true};
    for(int i=0; i<60; i++)
    {
        lastOut[i] =-1;
        lastIn[i] = -1;
        inDiff[i]=0;
        outDiff[i]=0;
        inDiffZeroCnt[i] = 0;      //yangmeng 161025 记录流量差值持续为0的次数
        outDiffZeroCnt[i] = 0;
    }
    for(int i=0; i<183; i++)
    {
        value[i] =0;
    }
  //  qDebug()<<"init out"<<lastOut[30]<<endl;

    Vb tem_vb;
    QString switchVersion="";
    in_sum=0;
    out_sum=0;
    qint32 lastRecTime = QDateTime::currentDateTime().toTime_t();
    bool normalFlag = true;		// gaohao Add 记录当前性能状态  true表示正常，flase表示异常
   while(!th_stop)  //线程循环
    {
        time_start=(double)clock();
        memset(value, 0, sizeof(value));
        in_sum=0;
        out_sum=0;
        cpuusage=0;
        double memUsed = 0, memFree = 0;
        error=0;
        for(int i=0; i<list.size();)
        {

            Pdu pdu;   // construct a Pdu object
            for(int j=0; j < 20 && i <list.size(); ++j) //Once 20 data
            {
                pdu += vb[i++];
          //      qDebug()<<"vb "<<vb[i-1].get_printable_oid();
            }

            status = snmp.get(pdu, *target);
            if (status == SNMP_CLASS_SUCCESS)
            {
                qDebug()<<endl<<"*********************************";

                time_end=(double)clock();
                error = 0;
                for (int i = 0; i < pdu.get_vb_count(); i++)
                {
                    pdu.get_vb(tem_vb, i);
                    QString flag = oidMap.value(tem_vb.get_oid());

                    qDebug()<<"oid:"<<tem_vb.get_oid().get_printable();
                    qDebug()<<"flag:"<<flag;
               //     if(!(flag.contains("ifOutOctets")||flag.contains("ifInOctets")))
               //         continue;
                    if(flag == "version")
                    {
                        switchVersion=QString(tem_vb.get_printable_value());
                        qDebug()<<switchVersion;
                    }
                    else if(flag == "MemoryUsed")
                    {
                        memUsed = QString(tem_vb.get_printable_value()).toULong();
                        qDebug()<<memUsed;

                    }
                    else if(flag == "MemoryFree")
                    {
                        memFree = QString(tem_vb.get_printable_value()).toULong();
                        qDebug()<<memFree;

                    }
                    else if(flag == "CPUUsagewendu")
                    {
                        cpuusage = QString(tem_vb.get_printable_value()).toDouble();
                        qDebug()<<cpuusage;

                    }
                    else if(flag.contains("ifInOctets"))
                    {
                        int ifNo = flag.replace("ifInOctets", "").toInt();                      
                        bool ok;
                        QString temp=QString(tem_vb.get_printable_value());
                        qDebug()<<"temp"<<temp;


                        if(temp.contains("0x"))
                        value[(ifNo - 1)*2 ]=QString(tem_vb.get_printable_value()).toLongLong(&ok,16);
                       else
                             value[(ifNo - 1)*2 ]=QString(tem_vb.get_printable_value()).toLongLong(&ok,10);
//                        if(switch_name=="H1"&&this->type=="60"&&flag.right(2)=="51")
//                        {
//                            qDebug()<<"in"<<QString(tem_vb.get_printable_value())<<endl;
//                            qDebug()<<"in"<<value[(ifNo - 1)*2 ]<<endl;
//                        }
                        QString str=QString::number(value[(ifNo - 1)*2 ]);
                        qDebug()<<str;
                    }
                    else if(flag.contains("ifOutOctets"))
                    {
                        int ifNo =  flag.replace("ifOutOctets","").toInt();
                        bool ok;
                        QString temp=QString(tem_vb.get_printable_value());
                        qDebug()<<"temp"<<temp;


                        if(temp.contains("0x"))
                             value[(ifNo - 1)*2 +1]=QString(tem_vb.get_printable_value()).toLongLong(&ok,16);
                       else
                             value[(ifNo - 1)*2 +1]=QString(tem_vb.get_printable_value()).toLongLong(&ok,10);
                        if(( value[(ifNo - 1)*2 +1]>-0.02 && value[(ifNo - 1)*2 +1]<0.02)&&(switch_name=="H1"&&this->type=="60"&&flag.right(2)=="52"))
                        {
                            qDebug()<<"error value222:"<<value[(ifNo - 1)*2 +1]<<QString(tem_vb.get_printable_value())<<endl;
                        }
                        QString str=QString::number(value[(ifNo - 1)*2 +1 ]);
                        qDebug()<<str;
                    }
                    else if(flag.contains("ifoperstatus"))
                    {
                        int ifNo =  flag.replace("ifoperstatus","").toInt();
                        value[120 + ifNo - 1] = QString(tem_vb.get_printable_value()).toDouble ();

                        QString str=QString(tem_vb.get_printable_value());
                        qDebug()<<str;

                    }
                }

             }
            else
            {
                 //qDebug()<<switch_name<<" SNMP Error: "<<snmp.error_msg(status)<<endl;
                 ++error;
                 continue;
            }
             qDebug()<<"*********************************END";
         }
        if(error > 2)
            return;
        else
            {
           // if(reached==false)
            //if (reached == false)
                    normalFlag = true;	// gaohao Modify  这里只是记录标记，需要等到下面所有waring判断后，在发送正常信息 原:emit sig_setNormal(switch_name);//交换机重新设置为正常
        }
        qint32 currentTime = QDateTime::currentDateTime().toTime_t();

        emit sig_version(switch_name,switchVersion);//banenxinxi

        if(memUsed !=0 && memFree !=0)
            memusage = abs(memUsed/(memUsed + memFree)*100);
        else
            memusage = 0;       
       // emit sig_finish(switch_name,cpuusage,memusage,time_end-time_start); //取得数据，发出信号
        //记录本交换机一个周期发送多少次snmp(oidXX.xml中的条目数除以20--每次读20个数据) yangmeng 161031 start
        int snmpTimes = 0;
        if(list.size()%20)
            snmpTimes = list.size()/20;
        else
            snmpTimes = list.size()/20+1;

        emit sig_finish(switch_name,cpuusage,memusage,(time_end-time_start)/snmpTimes); //取得数据，发出信号  yangmeng 161031 end

        double temp = temMaxValue; // gaohao 将直接读取数据库改为从内存中获取信息
        cpuusage=cpuusage*1;
         //cpu men 插入数据库

        if(cpuusage>temp)       //yangmeng 161101 整个if替换
        {
            QString select_sql;
            select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype=? and isdeal ='否'";
            sqlquery->prepare(select_sql);
            sqlquery->bindValue(0,switch_name);
            sqlquery->bindValue(1,"CPU温度过高");
            if(sqlquery->exec())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
            {
                int res_num = 0;
                sqlquery->next();
                res_num=sqlquery->value(0).toInt();
                sqlquery->finish();
                if (res_num == 0)
                {
                    emit sig_warning(switch_name,"CPU温度过高", "X");    //, "X" --qhy
                    emit insert_cpu_mem("CPU温度",cpuusage,"超限",switch_name);
                    emit sig_alarm(switch_name);        //yangmeng 161101
                    qDebug()<<__FILE__<<__LINE__<<"\n"
                           <<"CPU温度过高"
                           <<"\n";
                }
            }
            normalFlag = false;	// gaohao Add
        }
        else
        {
            if(currentTime - lastRecTime >= 60)     //正常性能1分钟记录1次
                emit insert_cpu_mem("CPU温度",cpuusage,"正常",switch_name);

            // gaohao Add  将当前CPU再数据库中的信息更新为已处理状态
//            sqlquery->exec(QString("select * from alarmcurrent   where  name='%1' and  isdeal='否'").arg(switch_name));
//            if(sqlquery->next()) // 证明由该记录
//            {
//                emit sig_cpu_mem_deal("CPU温度过高",0,"正常",switch_name);
//                     sig_alarm(switch_name);
//            }

            //yangmeng 161101
            QString select_sql;
            select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype='CPU温度过高' and isdeal ='否'";
            sqlquery->prepare(select_sql);
            sqlquery->bindValue(0,switch_name);            
            sqlquery->exec();
            if( sqlquery->next())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
            {
                int res_num = 0;
                res_num=sqlquery->value(0).toInt();
                sqlquery->finish();
                if (res_num != 0)
                {
                    sqlquery->prepare("delete from alarmcurrent where name = ? and alarmtype='CPU温度过高' and isdeal ='否'");
                    sqlquery->bindValue(0,switch_name);
                    sqlquery->exec();
                    sqlquery->prepare("update alarm set  lasttime=?,isdeal='是' where name=? and alarmtype='CPU温度过高' and isdeal ='否'");
                    sqlquery->bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    sqlquery->bindValue(1,switch_name);
                    sqlquery->exec();
                    sqlquery->finish();
                    //sqlquery->clear();
                    emit sig_cpu_mem_deal("CPU温度过高",0,"正常",switch_name);
                    emit sig_alarm(switch_name);
                }
            }
        }

        temp = memMaxValue;
        if(memusage>temp)       //yangmeng 161101 整个if替换
        {
            QString select_sql;
            select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype='内存使用率过高' and isdeal ='否'";
            sqlquery->prepare(select_sql);
            sqlquery->bindValue(0,switch_name);
            sqlquery->exec();
            if(sqlquery->next())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
            {
                int res_num = 0;
                res_num=sqlquery->value(0).toInt();
                sqlquery->finish();
                if (res_num == 0)
                {
                    emit sig_warning(switch_name,"内存使用率过高", "X");   //, "X"--qhy
                    emit insert_cpu_mem("内存",memusage,"超限",switch_name);
                    emit sig_alarm(switch_name);        //yangmeng 161101

                }
            }
            normalFlag = false;	// gaohao Add
        }
        else
        {
            if(currentTime - lastRecTime >= 60)             //正常性能1分钟记录1次
                emit insert_cpu_mem("内存",memusage,"正常",switch_name);

            //yangmeng 161101180
            QString select_sql;
            select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype='内存使用率过高' and isdeal ='否'";
            sqlquery->prepare(select_sql);
            sqlquery->bindValue(0,switch_name);            
            sqlquery->exec();
            if(sqlquery->next())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
            {
                int res_num = 0;
                res_num=sqlquery->value(0).toInt();
                sqlquery->finish();
                if (res_num != 0)
                {
                    sqlquery->prepare("delete from alarmcurrent where name = ? and alarmtype='内存使用率过高' and isdeal ='否'");
                    sqlquery->bindValue(0,switch_name);
                    sqlquery->exec();
                    sqlquery->prepare("update alarm set  lasttime=?,isdeal='是' where name=? and alarmtype='内存使用率过高' and isdeal ='否'");
                    sqlquery->bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    sqlquery->bindValue(1,switch_name);
                    sqlquery->exec();
                    sqlquery->finish();
                   // sqlquery->clear();
                    emit sig_cpu_mem_deal("CPU温度过高",0,"正常",switch_name);
                    emit sig_alarm(switch_name);
                }
            }
        }

        int i, j;
        int cnt = type.toInt()*2;
        double tmp_in = 0, tmp_out=0;

        for(i= 0; i< cnt; i++)// 计算端口速率
        {
            double diff;
            j=i/2;

            bool sigFlag=  false; // 标记当前端口是否被特殊设置的
            QMap<int,double>::iterator itor1;
            for ( itor1 = switchInSignalValue.begin(); itor1 != switchInSignalValue.end(); ++itor1 ) {
                if(itor1.key() == j+1)
                {
//                    if(switch_name == "A2" && (j+1)==49)      //yangmeng161101
                       sigFlag = true;
                        break;
                }
            }
            if(sigFlag == true)
                tmp_in = switchInSignalValue[j+1];
            else  {   //没有配置单个进阈值 ，直接读出整体默认值---qhy
                if (j>=48 || (j>=24 && (switch_name == "A3" || switch_name == "B3" || switch_name == "A5" || switch_name =="A6" || switch_name =="B5" || switch_name == "B6")))
                    tmp_in = fiber_in;   //A3,B3,A5,A6,B5,B6的25-28口为光口，其他交换机的49号之后的端口为光口
                else
                    tmp_in = ele_in;    //其余端口为电口
               }

            sigFlag=  false; // 标记当前端口是否被特殊设置的
            QMap<int,double>::iterator itor2;
            for ( itor2 = switchOutSignalValue.begin(); itor2 != switchOutSignalValue.end(); ++itor2 ) {
                  if(itor2.key() == j+1)
                  {
                         sigFlag = true;
                          break;
                   }
             }
             if(sigFlag == true)
                 tmp_out = switchOutSignalValue[j+1];
              else     //没有配置单个出阈值 ，直接读出整体默认值---qhy
                {
                if (j>=48 || (j>=24 && (switch_name == "A3" || switch_name == "B3" || switch_name ==  "A5" || switch_name =="A6" || switch_name =="B5" || switch_name == "B6")))
                    tmp_out = fiber_out;   //A3,B3,A5,A6,B5,B6的25-28口为光口，其他交换机的49号之后的端口为光口
                  else
                    tmp_out = ele_out;    //其余端口为电口
                }

            if(value[i]<lastIn[j])
                diff = 0xffffffffu - lastIn[j] + value[i];
            else if(value[i] == lastIn[j])
                diff = 0;
            else if( lastIn[j]<0)       //yangmeng
                diff = 0;
            else
                diff = value[i] - lastIn[j];
            //inDiff[j] = diff == 0 ? inDiff[j] : diff;//如果流量为0，就使用上次的值
            if(diff == 0)       //yangmeng 161025 如果差值为0，就使用上次的值，如果累计4次为0，则认为流量为0
            {
                if(inDiffZeroCnt[j] == 3)
                {
                    inDiff[j] = 0;
                }
                else
                {
                    inDiffZeroCnt[j]++;
                }
            }
            else
            {
                inDiffZeroCnt[j] = 0;
                inDiff[j] = diff;
            }
            in_sum+=inDiff[j];//  每个端口两次取值的差值计入总数
            inSpeed = inDiff[j] *8.0/(5.0*1024*1024);//计算速率，


            i++;
            if(value[i]<lastOut[j])
                diff = 0xffffffffu - lastOut[j] + value[i];
            else if (value[i] == lastOut[j])
                diff = 0;
            else if( lastOut[j]<0)       //yangmeng
                    diff = 0;
            else
                diff = value[i] - lastOut[j];
            //outDiff[j] = diff == 0 ? outDiff[j] : diff;//如果流量为0，就使用上次的值
            if(diff == 0)       //yangmeng 161025 如果差值为0，就使用上次的值，如果累计4次为0，则认为流量为0
            {
                if(outDiffZeroCnt[j] == 3)
                {
                    outDiff[j] = 0;
                }
                else
                {
                    outDiffZeroCnt[j]++;
                }
            }
            else
            {
                outDiffZeroCnt[j] = 0;
                outDiff[j] = diff;
            }
             out_sum+=outDiff[j];//  每个端口两次取值的差值计入总数，
             outSpeed= outDiff[j] *8.0/(5.0*1024*1024);//计算速率

            //防止第一个值超限
             if(lastIn[j]<0&&lastOut[j]<0)
           {
                  inSpeed=0;
                  outSpeed=0;
                  in_sum=0;
                  out_sum=0;
                 // qDebug()<<"shoudongzhilinhg"<<endl;
                  emit slg_port( switch_name, j ,0,0);
            }


             emit slg_port( switch_name, j ,inSpeed,outSpeed);  //read the port traffic ,for update

//             if(inSpeed>tmp_in||outSpeed>tmp_out)   每个超限和正常的判断独立执行，不把进与出端口捆绑---qhy 2016.11.3
//             {


                 if(inSpeed>tmp_in)
                 {
                     //确认当前没有此告警信息，才进行告警信号发送        yangmeng 161028
                     //1、拓扑界面上选中交换机的告警刷新
                     //2、告警查询数据库内容刷新
                     //3、性能离线查询数据库内容刷新

                    value[120+j] = switchWarn;
                     QString select_sql;
                     select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype=? and isdeal ='否'";
                     sqlquery->prepare(select_sql);
                     sqlquery->bindValue(0,switch_name);
                     sqlquery->bindValue(1,"端口"+QString::number(j+1)+"进速率过高");
                     sqlquery->exec();
//                     bool temp = sqlquery->exec();       //yangmeng 161101
//                     sqlquery->next();                             //yangmeng 161101
                     if( sqlquery->next())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
                     {
                         int res_num = 0;
                         res_num=sqlquery->value(0).toInt();
                         sqlquery->finish();
                         if (res_num == 0)
                         {
                             qDebug()<<"查到结果"<<res_num<<"端口"<<QString::number(j+1)<<"进速率超限"<<switch_name;
                             emit insert_portSpeed("端口"+QString::number(j+1)+"进速率",inSpeed,"超限",switch_name);
                             emit sig_warning(switch_name,"端口" + QString::number(j+1) + "进速率过高",QString::number(inSpeed));    //记录具体的端口速率-qhy, QString::number(inSpeed)
                             emit sig_alarm( switch_name );
                         }
                      }

                        normalFlag = false;	// gaohao Add
                  }

                 if(outSpeed>tmp_out)
                 {
                     //确认当前没有此告警信息，才进行告警信号发送        yangmeng 161028
                     //1、拓扑界面上选中交换机的告警刷新
                     //2、告警查询数据库内容刷新
                     //3、性能离线查询数据库内容刷新

                        value[120+j] = switchWarn;
                     QString select_sql;
                     select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype=? and isdeal ='否'";
                     sqlquery->prepare(select_sql);
                     sqlquery->bindValue(0,switch_name);
                     sqlquery->bindValue(1,"端口"+QString::number(j+1)+"出速率过高");         //yangmeng 161031
                     if(sqlquery->exec())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
                     {
                         int res_num = 0;
                         sqlquery->next();
                         res_num=sqlquery->value(0).toInt();
                         sqlquery->finish();
                         if (res_num == 0)
                         {
                             emit insert_portSpeed("端口"+QString::number(j+1)+"出速率",outSpeed,"超限",switch_name);
                             emit sig_warning(switch_name,"端口" + QString::number(j+1) + "出速率过高",QString::number(inSpeed));    //记录具体的端口速率-qhy, QString::number(outSpeed)
                             emit sig_alarm( switch_name );
                         }
                      }
                    normalFlag = false;	// gaohao Add
                 }



                 if (inSpeed<=tmp_in)
                 {
                     if(currentTime - lastRecTime >= 60)        //正常性能1分钟记录1次
                     {
                         emit insert_portSpeed("端口"+QString::number(j+1)+"进速率",inSpeed,"正常",switch_name);
                     }
                    QString select_sql;
                    select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype=? and isdeal ='否'";
                     sqlquery->prepare(select_sql);
                     sqlquery->bindValue(0,switch_name);
                     sqlquery->bindValue(1,"端口"+QString::number(j+1)+"进速率过高");
                     sqlquery->exec();

                     if(sqlquery->next())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
                     {
                         int res_num = 0;
                         res_num=sqlquery->value(0).toInt();
                         sqlquery->finish();
                         if (res_num > 0)
                         {
                             QString update_sql = "delete from alarmcurrent where name=? and alarmtype=? ";       //update alarmcurrent  set isdeal='是'
                             sqlquery->prepare(update_sql);
                             //sqlquery->bindValue(0,"是");
                             sqlquery->bindValue(0,switch_name);
                            sqlquery->bindValue(1,"端口"+QString::number(j+1)+"进速率过高");
                            sqlquery->exec();
                            sqlquery->finish();

                            update_sql = "update alarm set lasttime=?,isdeal='是' where name=? and alarmtype=? and isdeal='否' ";
                             sqlquery->prepare(update_sql);
                             sqlquery->bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));                            
                             sqlquery->bindValue(1,switch_name);
                             sqlquery->bindValue(2,"端口"+QString::number(j+1)+"进速率过高");
                            // qDebug()<<"switch="<<switch_name<<",alarmType = "<<"端口"+QString::number(j+1)+"进速率过高";
                            bool flag =  sqlquery->exec();
                            //qDebug()<<"testUpinfo"<<flag;
                             sqlquery->finish();

                             emit sig_alarm( switch_name );            //取消拓扑页面单个交换机的响应告警信息 yangmeng 161028
                             // emit sig_cancelWarning(switch_name);//取消告警状态
                         }
                     }
                 }

                  if (outSpeed<=tmp_out) {
                     if(currentTime - lastRecTime >= 60)        //正常性能1分钟记录1次
                     {
                         emit insert_portSpeed("端口"+QString::number(j+1)+"出速率",outSpeed,"正常",switch_name);
                     }


                    QString select_sql;
                     select_sql = "select count(*) from alarmcurrent where name = ? and alarmtype=? and isdeal ='否'";
                     sqlquery->prepare(select_sql);
                     sqlquery->bindValue(0,switch_name);
                     sqlquery->bindValue(1,"端口"+QString::number(j+1)+"出速率过高");
                     sqlquery->exec();
                     if(sqlquery->next())       //判断是否能够查询到结果，避免不必要的隐患      yangmeng 161028
                     {
                         int res_num = 0;
                         res_num=sqlquery->value(0).toInt();
                         //sqlquery->finish();
                         if (res_num > 0)
                         {
                             //qDebug()<<"查到结果"<<res_num<<"端口"<<QString::number(j+1)<<"出速率恢复"<<switch_name;
                            QString update_sql =  "delete from alarmcurrent where name=? and alarmtype=? ";
                            sqlquery->prepare(update_sql);
                            sqlquery->bindValue(0,switch_name);
                            sqlquery->bindValue(1,"端口"+QString::number(j+1)+"出速率过高");
                            sqlquery->exec();

                            update_sql = "update alarm set lasttime=?,isdeal='是' where name=? and alarmtype=? and isdeal='否' ";
                             sqlquery->prepare(update_sql);
                             sqlquery->bindValue(0,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));                             
                             sqlquery->bindValue(1,switch_name);
                             sqlquery->bindValue(2,"端口"+QString::number(j+1)+"出速率过高");
                             sqlquery->exec();
                             sqlquery->finish();
                            // sqlquery->clear();
                             emit sig_alarm( switch_name );            //取消拓扑页面单个交换机的响应告警信息 yangmeng 161028

                             //emit sig_cancelWarning(switch_name);
                         }
                     }

                 }

    //         }
           lastIn[j]=value[i-1];
           lastOut[j]=value[i];

           }


        in_sumG=in_sum/(1024*1024*1024);
        out_sumG=out_sum/(1024*1024*1024);
        in_sum=0;
        out_sum=0;
        emit sig_interfaceSum(switch_name,in_sumG,out_sumG);

        for(int i=120;i<+ this->type.toInt(); i++)//  读取端口状态,用120 + this->type代替180,因为各交换机的端口数不同---qhy 2016.11.07
        {

            emit sig_portStatus(switch_name,i - 120,value[i]);
            if(currentTime - lastRecTime >= 60 )     //正常性能1分钟记录1次
                emit insert_portStatus("端口"+QString::number(i-120+1)+"状态",value[i], "正常", switch_name);  //写入性能数据库中的描述修改，qhy---2016.11.07
        }
        //query.finish();
        //query.clear();

        if(currentTime - lastRecTime >= 60)     //正常性能1分钟记录1次-重新开始1个计时周期
        {
            lastRecTime = currentTime;
        }

        if (normalFlag == true)
        {
             emit sig_setNormal(switch_name);	//交换机重新设置为正常
        }


        msleep(2000);//yangmeng 161025  周期改为2s
    }
    //  delete target;
      Snmp::socket_cleanup();  // Shut down socket subsystem
}


void SwitchThread::stop()
{
    th_stop=true;
    wait();
}


