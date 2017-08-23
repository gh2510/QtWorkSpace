#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H
#include <QString>
/*
 *��˵����XML��ȡ�ࡣ�����ȡָ���ĵ�������xml��������
 *�����ˣ���?
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
    int getCombatPositionNum(); // ���������ļ����ص�ǰϵͳ��վλ������
    int getMaxRoleNum();  // ����ϵͳ��սλ������ɫ������
    QList<CombatPosition> getCombatPositionList();
    QList<AttemptRule> getAttemperRules();
private:
    int combatPositionNum; // ϵͳ�ڵ�սλ������
    int maxRoleNum; // ϵͳ�ڸ�սλ������ɫ������
private:
    QList<CombatPosition> combatPositionList; // ��ǰ�����ļ�������վλ�Ķ���
    QList<AttemptRule> attemperRules;  // ���ȹ����б� ��¼ÿ����ɫ�£�ÿ����Ļ��Ӧ��ҳ�����
};

#endif // CONFIGPARSE_H
