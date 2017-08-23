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
    static void WarnMessage(QString errInfo); // �����澯�Ի���
    
public:
    static CombatPosition currentCombatPosition; // ������վλ��Ϣ
    static Attemper *attmper; // ��������
    static DDSPublich ddsPublic; // DDS������
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
