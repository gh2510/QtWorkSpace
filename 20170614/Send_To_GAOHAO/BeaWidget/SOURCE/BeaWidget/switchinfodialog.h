#ifndef SWITCHINFODIALOG_H
#define SWITCHINFODIALOG_H

#include <QDialog>
#include<QTableView>
#include<QLabel>
#include"mystandarditemmodel.h"
#include"commonbutton.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
namespace Ui {
class SwitchInfoDialog;
}

class SwitchInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SwitchInfoDialog(QWidget *parent = 0);
    ~SwitchInfoDialog();
    void init_table();
    void setSwitch(QString name,QString location,QString num);
    void setList(QStringList list);
    myStandardItemModel * switchTableModel;
public slots:
    void slot_close();
    
private:
    Ui::SwitchInfoDialog *ui;

    QStringList state;
    QString fileName;
    int portNum;
};

#endif // SWITCHINFODIALOG_H
