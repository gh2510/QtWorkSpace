#ifndef USERDATATYPE_H
#define USERDATATYPE_H

#include <QString>
#include <QMap>
#include <QCheckBox>
#include "combatposition.h"

// 记录对应一个角色下，每个screenId对应的页面名称和代号
struct AttemptRule
{
    int roleId; // 角色ID号
    QMap<int,int> screenPage; // 每个screenId对应的显示页面 注 这里暂时先用名称，后续再考虑用代号还是名称 注意这里代号必须与客户端的页面匹配
};

// 记录当前每个checkbox对应的站位信息和角色信息
class CombatPosition;
struct CheckBoxInfo
{
    CombatPosition *combatPosition; // 对应的站位对象
    QCheckBox *checkbox; // 对应的checkbox对象
};

// 与画布通信之间的结构体
const unsigned short CLIENT_PORT = 5000;
const unsigned short SERVICE_PORT = 6000;
const unsigned char CANVAS_MSG_FLAG[4] = {0x0C,0x0A,0x0B,0x05};
const int MAX_NAME_LENGTH = 64;
struct CanvasMsg
{
    unsigned char flag[4]; // 报文标识
    unsigned char length; // 画布名字字节长度 最大为MAX_NAME_LENGTH
    char bak[2]; // 备份
    char canvasName[0]; // 画布名字，字节长度不能超过MAX_NAME_LENGTH
};

#endif // USERDATATYPE_H
