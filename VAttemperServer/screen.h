#ifndef SCREEN_H
#define SCREEN_H

#include <QString>

/*
 *��˵������Ӧսλ����ʾ���ࡣÿ����Ӧ��Ӧһ��������ڵ㣬�Լ�����������һ�����ȿͻ���
 *�����ˣ���?
 *ע�����
 *
 *
 */

class Screen
{
public:
    Screen();
public:
    int screenId; // ��ʾ������
    int width;   // ��Ļ�ֱ��ʿ��
    int height;  // ��Ļ�ֱ��ʸ߶�
    QString vmIp; // ��Ӧ�������IP��ַ
};

#endif // SCREEN_H
