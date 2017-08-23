#ifndef ROLESELECT_H
#define ROLESELECT_H

#include <QWidget>
#include "configparse.h"
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include "attemperform.h"
#include <QTextEdit>

/*
 *
 *��˵���������ࡣ������������ļ�����ʾ��ɫѡ����
 *
 *
 */

namespace Ui {
class RoleSelect;
}

class RoleSelect : public QWidget
{
    Q_OBJECT
    
public:
    explicit RoleSelect(QWidget *parent = 0);
    ~RoleSelect();
    void InitWidget(ConfigParse &configParse); // ���������ļ���Ϣ��ʼ��������ʾ
    void UpdateWidget();  // ��������һ��ʱ�����ݵ�ǰ�Ľ�ɫ��Ϣ������ʾ����
    
public slots:
    void okbtn_click(); // ���ȷ����Ӧ�¼�
    void cancelbtn_click(); // ����˳���Ӧ�¼�
    void checkbox_click(bool checked); // �����ɫ��Ӧ�¼�
private:
    Ui::RoleSelect *ui;
    QPushButton *okButton; // ȷ����ť
    QPushButton *cancelButton; // �˳���ť
    QButtonGroup *checkboxGroup;
    QList<CheckBoxInfo> checkInfoList; // ���и�ѡ�����
    AttemperForm *attemperForm;
    QTextEdit *descriptionedit; // ��ʾ��ɫ������Ϣ���ı�����
};

#endif // ROLESELECT_H
