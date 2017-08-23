#include "combatposition.h"

CombatPosition::CombatPosition()
{
}

CombatPosition::CombatPosition(const CombatPosition &combatPosition)
{
    this->estradeId = combatPosition.estradeId;
    this->estradeName = combatPosition.estradeName;
    Role role = combatPosition.getCurRole();
    this->SetCurRole(role);
    this->roleList.clear();
    for(int i=0;i<combatPosition.roleList.count();i++)
    {
        roleList.push_back(combatPosition.roleList.at(i));
    }
}
