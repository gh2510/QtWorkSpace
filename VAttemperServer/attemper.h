#ifndef ATTEMPER_H
#define ATTEMPER_H

#include <QList>
#include <QString>
#include "UserDataType.h"
#include "combatposition.h"
#include <QDataStream>
#include <QtNetwork/QUdpSocket>

/*
 * 类说明：调度类，负责根据配置文件中调度策略，判断在不同角色下，三个屏幕分别显示的页面代号和名称
 * 创建人： 高?
 *
 */
class Attemper
{
public:
    Attemper();
    QString ChangeRole(CombatPosition combatPosition); // 切换角色， 进行调度
private:
    QString Attepmer_To_HuaBuTool(QString roleName,int roleId); // 根据当前角色，向画布客户端下达本次调度方案
    QString Attemper_To_VM(QString vm_IP, int pageId = 0); // 接收调度信息并向远程虚拟机上的调度客户端发送调度指令
public:
    QList<AttemptRule> attemperRules;  // 调度规则列表 记录每个角色下，每个屏幕对应的页面代号
private:
    QUdpSocket udp_ToHuaBu;
};

#endif // ATTEMPER_H
