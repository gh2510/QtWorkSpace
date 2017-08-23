#include "telnetmanager.h"
#include <QListIterator>
#include<QDebug>

telnetManager::telnetManager():QThread()
{
    flag=REC_NOMAL;
    tel_status=0;
    telnet=new Telnet(this);
    incomeing= false;
    connect(telnet->tcpSocket,SIGNAL(readyRead()),this,SLOT(read_server()));
    connect(telnet->tcpSocket,SIGNAL(disconnected()),this,SIGNAL(signal_discon()));
    connect(telnet->tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SIGNAL(signal_error()));

    //connToServerandInit();
}
  int telnetManager::get_tel_status()
  {
      telnet->get_connected();
  }

int telnetManager::connToServerandInit(QString ob_ip,QString tel_pass,QString t_pass){
    telnet->set_ip(ob_ip);
   int res= telnet->connect_server();
   running = true;
   this->start();
   if(res==1)
   {
    this->query(tel_pass);
    this->query("enable");
    this->query(t_pass);
   }
   return res;
}
 void telnetManager::set_read_mode(int mode)
 {
     if(mode==0)
         this->flag=REC_NOMAL;
     else if(mode==1)
         this->flag=REC_QUERY;
 }

void telnetManager::confVlan(QString vlanId,QString ip, QList<int> portList){
//    if(flag!=0){
//        this->sendCmd("end");
//    }
    this->sendCmd("configure terminal");
    this->sendCmd("vlan "+vlanId);
    this->sendCmd("interface vlan"+vlanId);
    this->sendCmd("ip address "+ip+" 255.255.255.0");
    //QString msg="success! \n";
    QListIterator<int> i(portList);
    while(i.hasNext()){
        int portNum=i.next();

        this->sendCmd("interface f1/0/"+QString::number(portNum));
        this->sendCmd("switchport access vlan "+vlanId);
        //msg += port+" ";
    }
    this->sendCmd("exit");
    this->sendCmd("exit");
//    flag = REC_NOMAL;
    //msg += "is/are accessed to vlan"+vlanId+",its ip address is "+ip;
    //emit(readServer(msg));
}

void telnetManager::run()
{
    while(true)
    {
        runningMutex.lock();
        if(!running){
            runningMutex.unlock();
            return;
        }
        if(sem.tryAcquire())
        {
            if(commands.size() == 0)
                continue;
            mutex.lock();
            QString cmd = commands.front();
            commands.pop_front();
            mutex.unlock();
            this->sendCmd(cmd);
        }
        if(inMutex.tryLock())
        {
            if(incomeing)
            {
                incomeing = false;
                 inMutex.unlock();
                doRead();
            }
            else
            {
                inMutex.unlock();
            }
        }
        runningMutex.unlock();
    }
}

void telnetManager::query(QString queryCond){
    mutex.lock();
    commands.push_back(queryCond);
    sem.release();
    mutex.unlock();
}

void telnetManager::confPort(int portNum, QString portStatus, QString portMode, QString portSpeed){
//    if(flag!=0){
//        this->sendCmd("end");
//    }
    this->sendCmd("configure terminal");

    this->sendCmd("interface f1/0/"+portNum);
    QStringList speedSplit = portSpeed.split("M");
    QString speed = speedSplit[0];
    this->sendCmd("speed "+speed);
    this->sendCmd("switchport mode "+portMode);
    if(portStatus=="up"){
        this->sendCmd("no shut");
    }else{
        this->sendCmd("shutdown");
    }
    this->sendCmd("exit");
    this->sendCmd("exit");
//    flag = 0;
}

void telnetManager::doRead()
{
    char *readdata=( char *)(telnet->cs_communicate());

    if(readdata!=NULL)
    {
        txt_recv = QString((readdata));//QString(QLatin1String(readdata));
        // txt_recv=txt_recv.replace(QRegExp("[^a-zA-Z0-9-\\s]+"),"");
        if(txt_recv.contains("--More--")){
           copeWithMore(txt_recv);
        }else{
            if(flag==REC_QUERY)
            {
             emit(readServer(txt_recv));
            }
            else
            {
                return;
            }
        }
    }
    else
    {
        emit signal_discon();
    }
}

void telnetManager::read_server(){
    inMutex.lock();
    incomeing = true;
    inMutex.unlock();
}

void telnetManager::copeWithMore(QString txt_recv){
//    QStringList list = txt_recv.split("\n");
//    int l = list.length();
//    for(int i=0;i<l;i++){
//        if(list[i].trimmed()!=""&&!list[i].trimmed().contains("--More--"))
//        {
//            emit(readServer(list[i]));
//        }
//    }
    QString rec_str=txt_recv.replace("\033[7m--More--\033[m","");
    rec_str = rec_str.replace("\033[K", "");
    rec_str = rec_str.replace("\007", "");
    rec_str = rec_str.replace(QRegExp("[\r\n]+"), "\n");
    emit(readServer(rec_str));
    this->query("\r\n");
}

int  telnetManager::sendCmd(QString cmd){
    char *ch;
    QByteArray ba=cmd.toLatin1();
    ch=ba.data();
    return telnet->send_usrcommond(ch);

}
 void telnetManager::close_telnet()
 {
     runningMutex.lock();
     telnet->close_socket();
     running = false;
    runningMutex.unlock();
 }
telnetManager::~telnetManager(){
    telnet->close_socket();
}
