#ifndef COMBATPOSITION_H
#define COMBATPOSITION_H

#include <QString>
#include <QList>
#include "UserDataType.h"
#include "role.h"

/*
 *类说明：战位对象类，由于目前一个站位设备只能在一个站位工作，所以即可视为逻辑站位，也可视为一个设备站位。负责维护战位的信息。
 *       战位信息由XML配置文件读取。每个战位目前应该有三个屏组成，即对应三个虚拟机
 *       每个战位对应一个画布客户端，每个角色对应一个画布调度方案。
 *
 *创建人：高?
 *注意事项：
 *      目前暂定画布保存的调度文件名称规范：  角色代号_角色名称.
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
    int     estradeId; // 当前战位代号 -1表示站位对象无效
    QString estradeName; // 当前战位名称

    QList<Role> roleList; // 当前战位的角色列表
private:
    Role curRole;   // 当前站位已选择角色对象
};

#endif // COMBATPOSITION_H
