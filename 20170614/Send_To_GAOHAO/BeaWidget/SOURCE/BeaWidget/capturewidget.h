#ifndef CAPTUREWIDGET_H
#define CAPTUREWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QSpinBox>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QFileDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QApplication>
#include"captureimage.h"
#include"labeledit.h"
# include"commonbutton.h"
#include"capturethread.h"
#include "mystandarditemmodel.h"
namespace Ui {
class capturewidget;
}

class capturewidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit capturewidget(QWidget *parent = 0);
    ~capturewidget();
    void setFilePath(QString path);
    void setFileNum(int num);
    void initTabel();
private slots:


    void on_pushButton_set_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_reset_clicked();

private:
    Ui::capturewidget *ui;
    int typeCount;
     myStandardItemModel * switchTableModel;
     CaptureThread *captureThread,*captureThread1; // gaohao Add 捕获多个镜像口数据
};

#endif // CAPTUREWIDGET_H
