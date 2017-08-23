#include "ddspublich.h"

DDSPublich::DDSPublich()
{
}

/*
 * �������ƣ�InitDDS
 * �������ܣ���ʼ��DDS����
 * ������
 *     ��
 * ����ֵ��
 *     int 1��ʾ��ȷ��-1��ʾ����ʧ��
 *
 */
int DDSPublich::InitDDS()
{
    _RETURNCODE_T ret;

    int domainId = 10;

   //�����Ͷ��������������
    ret = DomainInit(domainId,"compName");

   if (ret != RETURNCODE_OK) //������
   {
       cout<<"Domain: "<<domainId <<" Init failed"<<endl;
       return 0;
   }

   //Ӧ�����QoS����
   _DATA_WRITER_QOS *qos = new _DATA_WRITER_QOS();
    qos->Reliability.Kind = BEST_EFFORT;

    //����������
    DataWriter * dataWriter = NULL;
    dataWriter = CreateDataWriter("compName",domainId, "V_PageAttemper", "V_PageAttemper", NULL, qos);

    if (dataWriter == NULL) //������
    {
        cout<<"Create Data Writer failed"<<endl;
        DomainRelease(domainId);
        return -1;
    }

    //��ȫ������ת��
    pageDataWriter = NULL;
    pageDataWriter = V_PageAttemperDataWriter::Narrow(dataWriter);

    if (pageDataWriter == NULL) //������
    {
        cout<<"myDataDataWriter Narrow failed"<<endl;
        DeleteDataWriter(dataWriter);
        DomainRelease(domainId);
        return -1;
    }
}

/*
 * �������ƣ�WriteAttemperInfo
 * �������ܣ����͵�����Ϣ
 * ������
 *     pageAttemper��������Ϣ�ṹ��
 * ����ֵ��
 *     DDS wirte����ֵ
 *
 *
 */
int DDSPublich::WriteAttemperInfo(V_PageAttemper pageAttemper)
{
    int ret = pageDataWriter->Write(pageAttemper);
    return ret;
}
