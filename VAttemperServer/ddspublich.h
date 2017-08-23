#ifndef DDSPUBLICH_H
#define DDSPUBLICH_H

#include <QString>
#include "DDS_API.h"

/*
 * 类说明：用于DDS发布消息的初始化
 *
 *
 */
class DDSPublich
{
public:
    DDSPublich();
    int InitDDS();
    int WriteAttemperInfo(V_PageAttemper pageAttemper); // 发送调度的信息
private:
    V_PageAttemperDataWriter *pageDataWriter;
};

#endif // DDSPUBLICH_H
