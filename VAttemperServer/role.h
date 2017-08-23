#ifndef ROLE_H
#define ROLE_H

#include <QString>
#include <QList>
#include "screen.h"

/*
 *��˵������Ӧ��ɫ��
 *�����ˣ���?
 *ע�����
 *
 *
 */

class Screen;
class Role
{
public:
    Role();
    int getRoleId() const
    {
        return roleId;
    }
    QString getRoleName() const
    {
        return roleName;
    }

    QString getDescription() const
    {
        return description;
    }

    QList<Screen> getScreenList() const
    {
        return screenList;
    }

    void setRoleId(int roleId)
    {
        this->roleId = roleId;
    }

    void setRoleName(QString roleName)
    {
        this->roleName = roleName;
    }
    void setDescription(QString description)
    {
        this->description = description;
    }
    void SetScreenList(QList<Screen> screenList)
    {
        this->screenList.clear();
        for(int i=0;i<screenList.count();i++)
        {
            this->screenList.push_back(screenList.at(i));
        }
    }

    void AddScreen(Screen screen)
    {
        screenList.push_back(screen);
    }


private:
    int roleId;   // ��ǰվλ��ѡ���ɫ�Ĵ��� -1��ʾվλ������Ч
    QString roleName;     // ��ǰվλ��ѡ��Ľ�ɫ����
    QString description;  // ��ɫ��Ϣ������
    QList<Screen> screenList; // ��ǰսλ��Ӧ������Ļ���ڵ�ǰ��ɫ�£�ÿ����Ļ��Ӧ��ҳ����Ϣ��ͬ
};

#endif // ROLE_H
