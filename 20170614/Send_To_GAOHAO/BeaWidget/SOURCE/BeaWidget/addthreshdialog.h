#ifndef ADDTHRESHDIALOG_H
#define ADDTHRESHDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
class AddThreshDialog:public QDialog
{
    Q_OBJECT
public:
    AddThreshDialog(QWidget *parent = 0);
    ~AddThreshDialog();
    QLineEdit * alarmNameLineEdit;
    QLineEdit * threshEdit;
    void setNameEn(bool);
private:
    QHBoxLayout *buttonLayout;
    QGridLayout *gLayout;
    QVBoxLayout *mainLayout ;
    QLabel * alarmnameLabel;
    QLabel * threshLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};


#endif // ADDTHRESHDIALOG_H
