#ifndef COMBATPOSITION_H
#define COMBATPOSITION_H

#include <QString>
#include <QList>
#include "UserDataType.h"
#include "role.h"

/*
 *��˵����սλ�����࣬����Ŀǰһ��վλ�豸ֻ����һ��վλ���������Լ�����Ϊ�߼�վλ��Ҳ����Ϊһ���豸վλ������ά��սλ����Ϣ��
 *       սλ��Ϣ��XML�����ļ���ȡ��ÿ��սλĿǰӦ������������ɣ�����Ӧ���������
 *       ÿ��սλ��Ӧһ�������ͻ��ˣ�ÿ����ɫ��Ӧһ���������ȷ�����
 *
 *�����ˣ���?
 *ע�����
 *      Ŀǰ�ݶ���������ĵ����ļ����ƹ淶��  ��ɫ����_��ɫ����.
 *
 */

class CombatPosition
{
public:
    CombatPosition();
    CombatPosition(const CombatPosition &combatPosition);
    void SetCurRole(Role curRole)
    {
        this->curRole.setRoleId(curRole.getRoleId());
        this->curRole.setRoleName(curRole.getRoleName());
        this->curRole.setDescription(curRole.getDescription());
        this->curRole.SetScreenList(curRole.getScreenList());
    }
    Role getCurRole() const
    {
        return curRole;
    }

public:
    int     estradeId; // ��ǰսλ���� -1��ʾվλ������Ч
    QString estradeName; // ��ǰսλ����

    QList<Role> roleList; // ��ǰսλ�Ľ�ɫ�б�
private:
    Role curRole;   // ��ǰվλ��ѡ���ɫ����
};

#endif // COMBATPOSITION_H
