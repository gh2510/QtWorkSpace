#ifndef SCREEN_H
#define SCREEN_H

#include <QString>

/*
 *类说明：对应战位的显示屏类。每个屏应对应一个虚拟机节点，以及虚拟机里面的一个调度客户端
 *创建人：高?
 *注意事项：
 *
 *
 */

class Screen
{
public:
    Screen();
public:
    int screenId; // 显示屏代号
    int width;   // 屏幕分辨率宽度
    int height;  // 屏幕分辨率高度
    QString vmIp; // 对应虚拟机的IP地址
};

#endif // SCREEN_H
