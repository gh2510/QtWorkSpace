#include "configparse.h"

/*
 *构造函数
 *
 */
ConfigParse::ConfigParse()
    :combatPositionNum(0),
    maxRoleNum(0)
{


}

/*
 *函数名称：pasreConfigFile
 *函数描述：读取xml中指定的xml文件，进行解析，将结果存入结构体中
 *参数输入：
 *        xmlPath: xml文件的路径
 *参数输出：
 *      QString:若解析正常返回“”，否则返回错误信息
 */
QString ConfigParse::pasreConfigFile(QString xmlPath)
{
    QString ret = "";
    QDomDocument document;
    QFile file(xmlPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       ret = "未找到配置文件，请确定final.xml文件存在";
       return ret;
     }
     else
     {
        if(!document.setContent(&file))
        {
            ret = "加载文件失败";
            return ret;
         }
         file.close();
      }
    // 获得根目录信息
    QDomElement root=document.documentElement();
    QDomNode combatPositionNode = root.firstChild();
    if(combatPositionNode.isNull()) // 未找到站位信息
    {
        ret = "配置文件中未获得站位信息，请核实";
        return ret;
    }


    while(!combatPositionNode.isNull())
    {
        AttemptRule attemperRule;
        Role role;
        QString strtemp = "";
        Screen screen;
        CombatPosition combatPosition;
        QDomElement combatPositionElement = combatPositionNode.toElement();
        if(!combatPositionElement.isNull())
        {
            // 获得站位代号和名称
            strtemp = combatPositionElement.attribute("cpId");
            combatPosition.estradeId = strtemp.toInt();
            strtemp = combatPositionElement.attribute("cpName");
            combatPosition.estradeName = strtemp;

            // 获得角色信息
            QDomNode roleNode = combatPositionElement.firstChild();
            while(!roleNode.isNull())
            {
                QDomElement roleElement = roleNode.toElement();
                strtemp = roleElement.attribute("roleId");
                role.setRoleId(strtemp.toInt());
                strtemp = roleElement.attribute("roleName");
                role.setRoleName(strtemp);
                strtemp = roleElement.attribute("description");
                role.setDescription(strtemp);
                combatPosition.roleList.push_back(role);

                // 获得屏幕信息
                QDomNode screenNode = roleElement.firstChild();
                while(!screenNode.isNull())
                {
                    QDomElement screenElement = screenNode.toElement();
                    strtemp = screenElement.attribute("screenId");
                    screen.screenId = strtemp.toInt();
                    strtemp = screenElement.attribute("width");
                    screen.width = strtemp.toInt();
                    strtemp = screenElement.attribute("height");
                    screen.height = strtemp.toInt();
                    strtemp = screenElement.attribute("vmIP");
                    screen.vmIp = strtemp;
                    role.AddScreen(screen);

                    // 生成规则信息
                    strtemp = screenElement.attribute("pageId");
                    int pageId = strtemp.toInt();
                    attemperRule.roleId = role.getRoleId();
                    attemperRule.screenPage.insert(screen.screenId,pageId);
                    attemperRules.push_back(attemperRule);

                    screenNode = screenNode.nextSibling();
                }
                roleNode = roleNode.nextSibling();
            }
        }

        combatPositionList.push_back(combatPosition);
        combatPositionNode = combatPositionNode.nextSibling();
    }

    return ret;
}

/*
 * 函数名称：getCombatPositionNum
 * 函数功能：根据配置文件返回当前系统内站位的数量
 * 参数：无
 * 返回值：
 *       当前系统内站位的数量
 *
 *
 */
int ConfigParse::getCombatPositionNum()
{
    return combatPositionList.count();
}

/*
 * 函数名称：getMaxRoleNum
 * 函数功能：根据配置文件返回战位中最大角色的数量
 * 参数：无
 * 返回值：
 *       战位中最大角色的数量
 *
 *
 */
int ConfigParse::getMaxRoleNum()
{
    for(int i=0;i<combatPositionList.count();i++)
    {
        if(combatPositionList.at(i).roleList.count() > maxRoleNum)
            maxRoleNum = combatPositionList.at(i).roleList.count();
    }
    return maxRoleNum;
}

/*
 * 函数名称：getCombatPositionList
 * 函数功能：获得所有站位的信息
 * 参数：无
 * 返回值：
 *       所有站位的信息
 *
 *
 */
QList<CombatPosition> ConfigParse::getCombatPositionList()
{
    return combatPositionList;
}

/*
 * 函数名称：getAttemperRules
 * 函数功能：获得所有映射规则信息
 * 参数：无
 * 返回值：
 *       所有规则的信息
 *
 *
 */
QList<AttemptRule> ConfigParse::getAttemperRules()
{
    return attemperRules;
}

