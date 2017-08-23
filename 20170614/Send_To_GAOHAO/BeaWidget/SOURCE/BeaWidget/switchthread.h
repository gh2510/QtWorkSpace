#ifndef SWITCHTHREAD_H
#define SWITCHTHREAD_H
#include <QThread>
#include "snmp_pp/snmp_pp.h"
#include <libsnmp.h>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QtXml>
#include "switchstateview.h" // gaohao Add
#include <QDebug>
#include <QSqlQuery>
#ifdef SNMP_PP_NAMESPACE
using namespace Snmp_pp;
#endif

class SwitchThread : public QThread
{
    Q_OBJECT
public:
    SwitchThread(QObject *parent = 0,QString name="");
    ~SwitchThread();
    static void InitSwitchComInfo(); // gaohao Add
    void stop();
signals:
    void sig_finish(QString  name,double cpuusage,double memusage,double delay);
     void slg_port(QString name,int portnumber,double in,double out);
     void sig_warning(QString switchName,QString alarmType,QString portSpeed);  //--qhy
     void sig_setNormal(QString switchName);
     void sig_portStatus(QString switchName,int portNumber,int status);
     void sig_version(QString switchName,QString version);
     void signal_switchSelected(QString,QString);
     void sig_alarm( QString );
     void insert_cpu_mem(QString type,double value,QString state,QString name);
     void insert_portSpeed(QString type,double value,QString state,QString name);
     void insert_portStatus(QString type,double value,QString state,QString name);
     void sig_interfaceSum(QString name,double inSum,double outSum);
     void sig_cpu_mem_deal(QString type,double value,QString state,QString name); // gaohao 1031 Add 该信号用于处理CPU和内存的正常状态
//    void sig_switch_down(int switchnumber);

public slots:
     void alarmSet(QString,int,int,double);  // gaohao Add 修改阈值时发送 分别时交换机名称 端口号 输入输出属性（0为输入 1为输出） 阈值信息
     void alarmDel(QString switchName,int port,int inout); // gaohao Add 删除特定阈值时发送 分别时交换机名称 端口号 输入输出属性（0为输入 1为输出的
     void alarmAdd(QString switchName, int port , int inout, double value); //yangmeng 161101

public:
     static double temMaxValue; // 温度阈值 gaohao Add
     static double memMaxValue; // 内存阈值 gaohao Add
     static double tmp_in; // 端口进入阈值 gaohao Add
     static double tmp_out; // 端口输出阈值 gaohao Add
     static double ele_in, ele_out, fiber_in, fiber_out; // 光口电口输入输出阈值 gaohao Add
private:
    QString switch_name;
    int error;
    QString ipaddress;
    QString backupAddr;
    QString mycommunity;
    bool  th_stop;
  bool reached;
   long double in_sum;
   long  double out_sum;
   double in_sumG;
   double out_sumG;
   QString type;
   virtual void run();
   void snmpQuery(QString ip);
    QSqlQuery *sqlquery;


    // goahao Add
   QMap<int,double> switchInSignalValue;// 记录特定设置输入阈值的端口 第一个参数为端口后第二个参数为阈值
   QMap<int,double> switchOutSignalValue;// 记录特定设置输出阈值的端口 第一个参数为端口后第二个参数为阈值
  // void oldRun();
};

#endif // SWITCHTHREAD_H
