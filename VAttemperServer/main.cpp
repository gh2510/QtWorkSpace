#include "mainwindow.h"
#include <QApplication>
#include "roleselect.h"
#include <QString>
#include <QTextCodec>

/*
 *�����ˣ���??
 *���ڣ�2017��8��17��
 *��Ʒ˵����
 *        �����Ϊ���⻯ƽ̨ͳһ��������ͻ��ˣ�����սλ̨�������ṩ���ڽ�ɫ�ĵ��ȹ��ܣ����Ƶ��ȿͻ��˺ͻ����ͻ��ˣ�����ԭ��ϵͳ
 *
 *�汾�ţ�
 *v1.0������
 */

#pragma comment(lib,"BLUEDCS.lib")

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

    // ��ȡ���������ļ�
    ConfigParse configParse;
    RoleSelect *roleSelectWidget = new RoleSelect();
    QString str = configParse.pasreConfigFile("final.xml");
    qDebug()<<str;

    MainWindow mainWindow;
    mainWindow.hide();
    if(str != "")
    {
        MainWindow::WarnMessage(str);
        exit(0);
    }

    // ��ʼ��DDS����
    int res = MainWindow::ddsPublic.InitDDS();
    if(res < 0)
    {
        MainWindow::WarnMessage("��ʼ��DDSʧ��");
    }

    roleSelectWidget->InitWidget(configParse);
    roleSelectWidget->show();
    return a.exec();
}
