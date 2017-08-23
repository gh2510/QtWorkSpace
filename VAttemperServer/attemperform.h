#ifndef ATTEMPERFORM_H
#define ATTEMPERFORM_H

#include <QHBoxLayout>
#include <mainwindow.h>
#include <combatposition.h>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

/*
 * ��˵���� ���ȴ����ࡣ������ʾ���Ƚ����ܣ������û��л���ɫ��ʵ��ҳ����ȡ�ͬʱ���Է��ص�֮ǰ��վλ
 * �����ˣ� ��?
 *
 *
 */
#include <QWidget>

namespace Ui {
class AttemperForm;
}

class AttemperForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AttemperForm(QWidget *frontWidget,QWidget *parent = 0);
    void UpdateForm(); // ���½����ϵ���Ϣ
    void InitWidget();
    ~AttemperForm();

public slots:
    void resbtn_click(); // ���������һ���¼�
    void exitbtn_click(); // ����˳����¼�
    void indexChanged(const QString &text);  // �л���ɫ���¼�
    
private:
    Ui::AttemperForm *ui;
    QLabel *cpLabel;  // վλ��Ϣ
    QComboBox *rlCombox; // ��ɫ�б�
    QPushButton *retBtn; // ������һ����ť
    QPushButton *exitBtn; // �˳���ť
    QWidget *frontWidget; // �򿪱����ڵ���һ������

};

#endif // ATTEMPERFORM_H
