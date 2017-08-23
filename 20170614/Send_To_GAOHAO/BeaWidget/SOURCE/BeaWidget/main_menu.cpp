#include "main_menu.h"

MainMenu::MainMenu(QWidget *parent): QMenu(parent)
{
    this->createActions();
    this->translateActions();
    this->setObjectName("menu");
}
void MainMenu::createActions()
{
    action_setting=new QAction(this);
    action_about_us=new QAction(this);

    this->addAction(action_setting);
    this->addAction(action_about_us);

    connect(action_setting,SIGNAL(triggered()),this,SIGNAL(showSettingDialog()));
    connect(action_about_us,SIGNAL(triggered()),this,SIGNAL(showAboutUs()));

}

void MainMenu::translateActions()
{
    action_setting->setText(tr("设置"));
    action_about_us->setText(tr("关于我们"));
}
