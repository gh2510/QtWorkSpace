#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include "defcommon.h"

class MainMenu : public QMenu
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent=0);
    void translateActions();
signals:
    void showSettingDialog();
    void showNewCharacter();
    void showAboutUs();
//private slots:
//    void showPage();
private:
    void createActions();
private:
    QAction *action_setting;//set param
    QAction *action_about_us;//about us
};

#endif // MAIN_MENU_H
