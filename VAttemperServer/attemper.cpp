#include "attemper.h"
#include "mainwindow.h"

Attemper::Attemper()
{

}

/*
 *
 *�������ܣ����յ�����Ϣ����Զ��������ϵĵ��ȿͻ��˷��͵���ָ��
 * ����
 *    vm_IP��  ��ǰ��ʾ�������IP��ַ
 *    pageId;  ��ǰ��ʾ��ҳ�����  ע��Ҫ��ͻ��������ļ�����ƥ��
 *����ֵ��
 *    QString��
 *             ������ʾ�ɹ������򷵻ش�����Ϣ
 *
 */
QString Attemper::Attemper_To_VM(QString vm_IP,int pageId)
{
    // ͨ��DDS��ͻ��˷����������� V_PageAttemper
    QString strSign= "";
    V_PageAttemper pageAttemper;
    QByteArray bytename = vm_IP.toLatin1();
    memcpy(pageAttemper.IP,bytename.data(),15);
    pageAttemper.pageId = pageId;
    int res = MainWindow::ddsPublic.WriteAttemperInfo(pageAttemper);
    if(res != RETURNCODE_OK)
    {
        strSign = "DDS���ͷ��ش������ " + res;
    }
    return strSign;
}

/*
 * �������ܣ������ɫID�����ݵ�ǰ��ɫ��ɵ��ȿͻ����뻭���ͻ��˵ĵ���
 * ������
 *     combatPosition����վλ����Ϣ
 * ����ֵ��
 *     QString��������ʾ��ȷ�����򷵻ش�����Ϣ
 *
 *
 *
 */
QString Attemper::ChangeRole(CombatPosition combatPosition)
{
    // �������򣬲��ҵ���Ӧ�Ĺ���
    QString strSign = "";
    for(int i=0;i<attemperRules.count();i++)
    {
        Role curRole = combatPosition.getCurRole();
        if(attemperRules[i].roleId == curRole.getRoleId()) // �ҵ���սλ��Ӧ�Ľ�ɫ��
        {
            // ���ȶԵ��ȿͻ��˽��е��ȣ�������Ӧ��ͼԪ
            for(int j=0;j<curRole.getScreenList().count();j++) // ����������ÿ����Ļ����Ϣ
            {
               // ����screenPage �ҵ�ÿ��ҳ���Ӧ��pageId��Ϣ
                int screenId = curRole.getScreenList().at(j).screenId; // �ҵ���Ӧ����Ļ����
                QMap<int, int>::iterator it = attemperRules[i].screenPage.find(screenId);
                if (it == attemperRules[i].screenPage.constEnd())  // ��ʾΪ�ҵ���ǰҳ���Ӧ�Ĺ���
                {
                    continue; // ��ʱ����
                }
                // ��ʾ�ҵ���ǰ��Ӧ�Ĺ���
                int pageId = it.value(); // �ҵ���Ӧ��ҳ����Ϣ
                strSign = Attemper_To_VM(curRole.getScreenList().at(j).vmIp,pageId);
                if(strSign != "") // �жϵ����Ƿ�ɹ� ��ʧ������ֹ�������ȣ�ֱ�ӷ���
                   return strSign;
            }
            // �Ի����ͻ��˽��е���
            strSign = Attepmer_To_HuaBuTool(curRole.getRoleName(),curRole.getRoleId());
            if(strSign != "")
                return strSign;
            break;
        }
    }
    return strSign;
}

/*
 *
 * �������ܣ����ݵ�ǰ��ɫ��Ϣ�����ɻ����������ƣ�ͨ�����緢�͸������ͻ���
 * ������
 *      roleName����ǰ��ɫ����
 *      roleId����ǰ��ɫId
 * ����ֵ��
 *     int:
 *        0>����ʾ�ɹ� ���ط����ֽڵĳ���
 *        -1����ʾȱʧ��ɫ��Ϣ���޷�����
 *
 *
 */
QString Attemper::Attepmer_To_HuaBuTool(QString roleName, int roleId)
{
    QString ret = "";
    roleName = roleName; // ��������Ϊ  ��ɫ����
    // ͨ��UDP�������������� V_HB_Attemper
    CanvasMsg canvasMsg;
    // ���ı�ʶ
    memcpy(canvasMsg.flag,CANVAS_MSG_FLAG,4);
    canvasMsg.length = roleName.length();
    QByteArray bytename = roleName.toLatin1();
    memcpy(canvasMsg.canvasName, bytename.data(),roleName.length());

    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out<<&canvasMsg;
    // ��������
    int flag = udp_ToHuaBu.writeDatagram(datagram,QHostAddress::LocalHost,CLIENT_PORT); // ������������ͻ�����ͬһ̨�豸Ĭ�Ͼ��Ǳ���
    if(flag <= 0)
        ret = "���͸����ȷ������������ʧ��";
    return ret;
}

