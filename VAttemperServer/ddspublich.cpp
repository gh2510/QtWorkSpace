#include "ddspublich.h"

DDSPublich::DDSPublich()
{
}

/*
 * 函数名称：InitDDS
 * 函数功能：初始化DDS发布
 * 参数：
 *     无
 * 返回值：
 *     int 1表示正确，-1表示创建失败
 *
 */
int DDSPublich::InitDDS()
{
    _RETURNCODE_T ret;

    int domainId = 10;

   //将发送端组件加入数据域
    ret = DomainInit(domainId,"compName");

   if (ret != RETURNCODE_OK) //出错处理
   {
       cout<<"Domain: "<<domainId <<" Init failed"<<endl;
       return 0;
   }

   //应用组件QoS设置
   _DATA_WRITER_QOS *qos = new _DATA_WRITER_QOS();
    qos->Reliability.Kind = BEST_EFFORT;

    //创建发布者
    DataWriter * dataWriter = NULL;
    dataWriter = CreateDataWriter("compName",domainId, "V_PageAttemper", "V_PageAttemper", NULL, qos);

    if (dataWriter == NULL) //出错处理
    {
        cout<<"Create Data Writer failed"<<endl;
        DomainRelease(domainId);
        return -1;
    }

    //安全的类型转换
    pageDataWriter = NULL;
    pageDataWriter = V_PageAttemperDataWriter::Narrow(dataWriter);

    if (pageDataWriter == NULL) //出错处理
    {
        cout<<"myDataDataWriter Narrow failed"<<endl;
        DeleteDataWriter(dataWriter);
        DomainRelease(domainId);
        return -1;
    }
}

/*
 * 函数名称：WriteAttemperInfo
 * 函数功能：发送调度信息
 * 参数：
 *     pageAttemper：调度信息结构体
 * 返回值：
 *     DDS wirte返回值
 *
 *
 */
int DDSPublich::WriteAttemperInfo(V_PageAttemper pageAttemper)
{
    int ret = pageDataWriter->Write(pageAttemper);
    return ret;
}
