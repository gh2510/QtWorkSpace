#ifndef ATTEMPER_H
#define ATTEMPER_H

#include <QList>
#include <QString>
#include "UserDataType.h"
#include "combatposition.h"
#include <QDataStream>
#include <QtNetwork/QUdpSocket>

/*
 * ��˵���������࣬������������ļ��е��Ȳ��ԣ��ж��ڲ�ͬ��ɫ�£�������Ļ�ֱ���ʾ��ҳ����ź�����
 * �����ˣ� ��?
 *
 */
class Attemper
{
public:
    Attemper();
    QString ChangeRole(CombatPosition combatPosition); // �л���ɫ�� ���е���
    void AddAttemperRules(QList<AttemptRule> templist)
    {
        for(int i=0;i<templist.count();i++)
        {
            attemperRules.push_back(templist.at(i));
        }
    }

private:
    QString Attepmer_To_HuaBuTool(QString roleName,int roleId); // ���ݵ�ǰ��ɫ���򻭲��ͻ����´ﱾ�ε��ȷ���
    QString Attemper_To_VM(QString vm_IP, int pageId = 0); // ���յ�����Ϣ����Զ��������ϵĵ��ȿͻ��˷��͵���ָ��
private:
    QList<AttemptRule> attemperRules;  // ���ȹ����б� ��¼ÿ����ɫ�£�ÿ����Ļ��Ӧ��ҳ�����
private:
    QUdpSocket udp_ToHuaBu;
};

#endif // ATTEMPER_H
