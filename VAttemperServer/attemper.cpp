#include "attemper.h"
#include "mainwindow.h"

Attemper::Attemper()
{

}

/*
 *
 *函数功能：接收调度信息并向远程虚拟机上的调度客户端发送调度指令
 * 参数
 *    vm_IP：  当前显示的虚拟机IP地址
 *    pageId;  当前显示的页面代号  注意要与客户端配置文件内容匹配
 *返回值：
 *    QString：
 *             “”表示成功，否则返回错误信息
 *
 */
QString Attemper::Attemper_To_VM(QString vm_IP,int pageId)
{
    // 通过DDS向客户端发布调度命令 V_PageAttemper
    QString strSign= "";
    return strSign;
}

/*
 * 函数功能：输入角色ID，根据当前角色完成调度客户端与画布客户端的调度
 * 参数：
 *     combatPosition：本站位的信息
 * 返回值：
 *     QString：“”表示正确，否则返回错误信息
 *
 *
 *
 */
QString Attemper::ChangeRole(CombatPosition combatPosition)
{
    // 遍历规则，查找到相应的规则
    QString strSign = "";
    for(int i=0;i<attemperRules.count();i++)
    {
        Role curRole = combatPosition.getCurRole();
        if(attemperRules[i].roleId == curRole.getRoleId()) // 找到本战位对应的角色的
        {
            // 首先对调度客户端进行调度，启动相应的图元
            for(int j=0;j<curRole.getScreenList().count();j++) // 遍历规则下每个屏幕的信息
            {
               // 遍历screenPage 找到每个页面对应的pageId信息
                int screenId = curRole.getScreenList().at(j).screenId; // 找到对应的屏幕代号
                QMap<int, int>::iterator it = attemperRules[i].screenPage.find(screenId);
                if (it == attemperRules[i].screenPage.constEnd())  // 表示为找到当前页面对应的规则
                {
                    continue; // 暂时跳过
                }
                // 表示找到当前对应的规则
                int pageId = it.value(); // 找到对应的页面信息
                strSign = Attemper_To_VM(curRole.getScreenList().at(j).vmIp,pageId);
                if(strSign != "") // 判断调度是否成功 若失败则终止画布调度，直接返回
                   return strSign;
            }
            // 对画布客户端进行调度
            strSign = Attepmer_To_HuaBuTool(curRole.getRoleName(),curRole.getRoleId());
            return strSign;
        }
    }
    strSign = "找不到该角色匹配的调度规则，请确认";
    return strSign;
}

/*
 *
 * 函数功能：根据当前角色信息，生成画布方案名称，通过网络发送给画布客户端
 * 参数：
 *      roleName：当前角色名称
 *      roleId：当前角色Id
 * 返回值：
 *     int:
 *        0>：表示成功 返回发送字节的长度
 *        -1：表示缺失角色信息，无法生成
 *
 *
 */
int Attemper::Attepmer_To_HuaBuTool(QString roleName, int roleId)
{
    QString huabu_Name;
    roleName = roleName; // 画布方案为  角色名称
    // 通过UDP将画布方案发送 V_HB_Attemper
    CanvasMsg canvasMsg;
    // 报文标识
    memcpy(canvasMsg.flag,CANVAS_MSG_FLAG,4);
    canvasMsg.length = roleName.length();
    QByteArray bytename = roleName.toLatin1();
    memcpy(canvasMsg.canvasName, bytename.data(),roleName.length());

    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out<<&canvasMsg;
    // 发送数据
    int flag = udp_ToHuaBu.writeDatagram(datagram,QHostAddress::LocalHost,CLIENT_PORT); // 画布和虚拟机客户端在同一台设备默认就是本机
    return flag;
}

