#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "attemper.h"
#include "combatposition.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public:
    static CombatPosition currentCombatPosition; // 本机的站位信息
    static Attemper *attmper; // 调度引擎
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
