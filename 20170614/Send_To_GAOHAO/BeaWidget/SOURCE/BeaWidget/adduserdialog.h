#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
class AddUserDialog:public QDialog
{
    Q_OBJECT
public:
    AddUserDialog(QWidget *parent = 0);
    ~AddUserDialog();
    QLineEdit * userNameLineEdit;
    QLineEdit * passwordLineEdit;
    QComboBox * userlevelEdit;
    void setNameEn(bool flag);
private:
    QGridLayout *gLayout;
    QHBoxLayout *buttonLayout ;
    QVBoxLayout *mainLayout ;
    QLabel * nameLabel;
    QLabel * passwordLabel;
    QLabel * userlevelLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};
#endif // ADDUSERDIALOG_H
