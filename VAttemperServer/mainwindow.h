#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "attemper.h"
#include "combatposition.h"
#include "ddspublich.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static void WarnMessage(QString errInfo); // 弹出告警对话框
    
public:
    static CombatPosition currentCombatPosition; // 本机的站位信息
    static Attemper *attmper; // 调度引擎
    static DDSPublich ddsPublic; // DDS发布端
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
