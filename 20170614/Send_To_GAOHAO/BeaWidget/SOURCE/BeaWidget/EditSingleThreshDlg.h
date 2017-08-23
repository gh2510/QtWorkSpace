#ifndef EDITSINGLETHRESHDLG_H
#define EDITSINGLETHRESHDLG_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include<QSpinBox>
#include <QGridLayout>
class EditSingleThreshDlg:public QDialog
{
    Q_OBJECT
public:
    EditSingleThreshDlg(QWidget *parent = 0);
    ~EditSingleThreshDlg();
    QComboBox * switchName;
    QSpinBox * switchPort;
    QComboBox * type;
    QLineEdit * value;
public slots:
    void slot_indexChanged(QString  name);
private:
    QHBoxLayout *buttonLayout;
    QGridLayout *gLayout;
    QVBoxLayout *mainLayout ;
    QLabel * switchnameLabel;
    QLabel * switchportLabel;
    QLabel * typeLabel;
    QLabel * valueLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};


#endif // EDITSINGLETHRESHDLG_H
