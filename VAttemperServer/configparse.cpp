#include "configparse.h"

/*
 *���캯��
 *
 */
ConfigParse::ConfigParse()
    :combatPositionNum(0),
    maxRoleNum(0)
{


}

/*
 *�������ƣ�pasreConfigFile
 *������������ȡxml��ָ����xml�ļ������н��������������ṹ����
 *�������룺
 *        xmlPath: xml�ļ���·��
 *���������
 *      QString:�������������ء��������򷵻ش�����Ϣ
 */
QString ConfigParse::pasreConfigFile(QString xmlPath)
{
    QString ret = "";
    QDomDocument document;
    QFile file(xmlPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       ret = "δ�ҵ������ļ�����ȷ��final.xml�ļ�����";
       return ret;
     }
     else
     {
        if(!document.setContent(&file))
        {
            ret = "�����ļ�ʧ��";
            return ret;
         }
         file.close();
      }
    // ��ø�Ŀ¼��Ϣ
    QDomElement root=document.documentElement();
    QDomNode combatPositionNode = root.firstChild();
    if(combatPositionNode.isNull()) // δ�ҵ�վλ��Ϣ
    {
        ret = "�����ļ���δ���վλ��Ϣ�����ʵ";
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
            // ���վλ���ź�����
            strtemp = combatPositionElement.attribute("cpId");
            combatPosition.estradeId = strtemp.toInt();
            strtemp = combatPositionElement.attribute("cpName");
            combatPosition.estradeName = strtemp;

            // ��ý�ɫ��Ϣ
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

                // �����Ļ��Ϣ
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

                    // ���ɹ�����Ϣ
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
 * �������ƣ�getCombatPositionNum
 * �������ܣ����������ļ����ص�ǰϵͳ��վλ������
 * ��������
 * ����ֵ��
 *       ��ǰϵͳ��վλ������
 *
 *
 */
int ConfigParse::getCombatPositionNum()
{
    return combatPositionList.count();
}

/*
 * �������ƣ�getMaxRoleNum
 * �������ܣ����������ļ�����սλ������ɫ������
 * ��������
 * ����ֵ��
 *       սλ������ɫ������
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
 * �������ƣ�getCombatPositionList
 * �������ܣ��������վλ����Ϣ
 * ��������
 * ����ֵ��
 *       ����վλ����Ϣ
 *
 *
 */
QList<CombatPosition> ConfigParse::getCombatPositionList()
{
    return combatPositionList;
}

/*
 * �������ƣ�getAttemperRules
 * �������ܣ��������ӳ�������Ϣ
 * ��������
 * ����ֵ��
 *       ���й������Ϣ
 *
 *
 */
QList<AttemptRule> ConfigParse::getAttemperRules()
{
    return attemperRules;
}

