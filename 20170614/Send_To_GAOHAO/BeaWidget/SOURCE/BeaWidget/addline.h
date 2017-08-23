#ifndef ADDLINE_H
#define ADDLINE_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QStringList>
#include <QVBoxLayout>
#include "pushbutton_diy.h"
class AddLine : public QDialog
{
    Q_OBJECT
public:
    explicit AddLine(QStringList unswitchname,QStringList selectswitchname, QWidget *parent = 0);

    QListWidget *unselect_list;
    QListWidget *select_list;
    ~AddLine();

private:
    QLabel * lblunselect;
    QLabel * lblselect;
    PushButtonDIY* btnRight;
    PushButtonDIY* btnLeft;

    QPushButton *okButton;
    QPushButton *cancelButton;

    QStringList unswitchnamelist;
    QStringList selectswitchnamelist;

    QVBoxLayout * left_layout;
    QVBoxLayout * center_layout;
    QVBoxLayout * right_layout;
    QHBoxLayout *top_layout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout * main_layout;
signals:

public slots:
    void select_right();
    void ubselect_left();

};

#endif // ADDLINE_H
