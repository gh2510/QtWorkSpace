#ifndef ERRORDEAL_H
#define ERRORDEAL_H

#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QBoxLayout>
#include<QDateTime>
#include<QDebug>
#include<QTableWidgetItem>
#include<QMessageBox>
#include "commonbutton.h"
#include "mystandarditemmodel.h"
#include<QTimer>
namespace Ui {
class ErrorDeal;
}

class ErrorDeal : public QWidget
{
    Q_OBJECT
    
public:
    explicit ErrorDeal(QWidget *parent = 0);
    ~ErrorDeal();
    void init_table();
public slots:
    void updateAlarm();
    void refresh();
signals:
    void sig_cancelWarning(QString switchName);
private:
    Ui::ErrorDeal *ui;
    myStandardItemModel * switchTableModel;
    QTableView *tableview;
    commonButton *btn_add ;
    commonButton *btn_refresh ;
   QHBoxLayout *bottom_layout;
   QVBoxLayout *mainLayout;
  QTimer *time;
};

#endif // ERRORDEAL_H
