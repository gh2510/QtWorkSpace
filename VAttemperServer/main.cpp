#include "mainwindow.h"
#include <QApplication>
#include "roleselect.h"
#include <QString>
#include <QTextCodec>

/*
 *创建人：高暠
 *日期：2017年8月17日
 *产品说明：
 *        本软件为虚拟化平台统一调度软件客户端，运行战位台，负责提供基于角色的调度功能，控制调度客户端和画布客户端，调度原型系统
 *
 *版本号：
 *v1.0：创建
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("gbk"); // UTF-8
    QTextCodec::setCodecForTr(codec);

    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);


    /*QFile file(":/qrc/res/qtstyles.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);
    file.close();*/

    // 读取解析配置文件

    ConfigParse configParse;
    RoleSelect *roleSelectWidget = new RoleSelect();
    QString str = configParse.pasreConfigFile("final.xml");
    if(str != "")
        QMessageBox::information(roleSelectWidget,"错误提示",str,QMessageBox::Ok);

    roleSelectWidget->InitWidget(configParse);
    roleSelectWidget->show();
    return a.exec();
}
