#ifndef USERDATATYPE_H
#define USERDATATYPE_H

#include <QString>
#include <QMap>
#include <QCheckBox>
#include "combatposition.h"

// ��¼��Ӧһ����ɫ�£�ÿ��screenId��Ӧ��ҳ�����ƺʹ���
struct AttemptRule
{
    int roleId; // ��ɫID��
    QMap<int,int> screenPage; // ÿ��screenId��Ӧ����ʾҳ�� ע ������ʱ�������ƣ������ٿ����ô��Ż������� ע��������ű�����ͻ��˵�ҳ��ƥ��
};

// ��¼��ǰÿ��checkbox��Ӧ��վλ��Ϣ�ͽ�ɫ��Ϣ
class CombatPosition;
struct CheckBoxInfo
{
    CombatPosition *combatPosition; // ��Ӧ��վλ����
    QCheckBox *checkbox; // ��Ӧ��checkbox����
};

// �뻭��ͨ��֮��Ľṹ��
const unsigned short CLIENT_PORT = 5000;
const unsigned short SERVICE_PORT = 6000;
const unsigned char CANVAS_MSG_FLAG[4] = {0x0C,0x0A,0x0B,0x05};
const int MAX_NAME_LENGTH = 64;
struct CanvasMsg
{
    unsigned char flag[4]; // ���ı�ʶ
    unsigned char length; // ���������ֽڳ��� ���ΪMAX_NAME_LENGTH
    char bak[2]; // ����
    char canvasName[0]; // �������֣��ֽڳ��Ȳ��ܳ���MAX_NAME_LENGTH
};

#endif // USERDATATYPE_H
