#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H
#include <QString>
/*
 *类说明：XML读取类。负责读取指定的调度配置xml并解析。
 *创建人：高暠
 *
 */

#include "combatposition.h"
#include <QtXml/qdom.h>
#include <QtXml/qxml.h>
#include <QtXml/QDomElement>
#include "qxmlstream.h"

class ConfigParse
{
public:
    ConfigParse();
    QString pasreConfigFile(QString xmlPath);
    int getCombatPositionNum(); // 根据配置文件返回当前系统内站位的数量
    int getMaxRoleNum();  // 根据系统内战位中最大角色的数量
    QList<CombatPosition> getCombatPositionList();
    QList<AttemptRule> getAttemperRules();
private:
    int combatPositionNum; // 系统内的战位的数量
    int maxRoleNum; // 系统内各战位中最大角色的数量
private:
    QList<CombatPosition> combatPositionList; // 当前配置文件中所有站位的对象
    QList<AttemptRule> attemperRules;  // 调度规则列表 记录每个角色下，每个屏幕对应的页面代号
};

#endif // CONFIGPARSE_H
