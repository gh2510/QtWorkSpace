#ifndef DDSPUBLICH_H
#define DDSPUBLICH_H

#include <QString>
#include "DDS_API.h"

/*
 * ��˵��������DDS������Ϣ�ĳ�ʼ��
 *
 *
 */
class DDSPublich
{
public:
    DDSPublich();
    int InitDDS();
    int WriteAttemperInfo(V_PageAttemper pageAttemper); // ���͵��ȵ���Ϣ
private:
    V_PageAttemperDataWriter *pageDataWriter;
};

#endif // DDSPUBLICH_H
