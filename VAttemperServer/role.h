#ifndef ROLE_H
#define ROLE_H

#include <QString>
#include <QList>
#include "screen.h"

/*
 *类说明：对应角色类
 *创建人：高?
 *注意事项：
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
    int roleId;   // 当前站位已选择角色的代号 -1表示站位对象无效
    QString roleName;     // 当前站位已选择的角色名称
    QString description;  // 角色信息的描述
    QList<Screen> screenList; // 当前战位对应若干屏幕，在当前角色下，每个屏幕对应的页面信息不同
};

#endif // ROLE_H
