#ifndef ATTEMPERPAGE_H
#define ATTEMPERPAGE_H

#include <QWidget>

/*
 *��˵���������࣬�����ȡ�����ļ������ݣ����սλ�ͽ�ɫѡ��ҳ�����ʾ��ͬʱ�����û���������������������ɵ���
 *�����ˣ���?
 *ע���������Ĭ�϶�ȡ���г���ͬĿ¼�µ�finalServer.xml�ļ�
 *
 *
 */

namespace Ui {
class AttemperPage;
}

class AttemperPage : public QWidget
{
    Q_OBJECT
    
public:
    explicit AttemperPage(QWidget *parent = 0);
    ~AttemperPage();
    
private:
    Ui::AttemperPage *ui;
};

#endif // ATTEMPERPAGE_H
