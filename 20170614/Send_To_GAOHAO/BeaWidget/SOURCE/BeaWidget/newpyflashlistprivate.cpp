#include "newpyflashlistprivate.h"
#include "ui_newpyflashlistprivate.h"
#include <QPushButton>

NewPYFlashListPrivate::NewPYFlashListPrivate(int hei, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewPYFlashListPrivate)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    buttonHeight = hei;
}

NewPYFlashListPrivate::~NewPYFlashListPrivate()
{
    clear();
    delete ui;
}

//add new button
void NewPYFlashListPrivate::addItem(const QString &str)
{
    newButton = new QPushButton(ui->widget_button);
    newButton->setFixedSize(this->width()-2,buttonHeight);
    newButton->setText(str);
    newButton->setObjectName(str);
    connect(newButton,SIGNAL(clicked()),this,SLOT(updateButtonList()));
    buttonList.append(newButton);
    ui->verButton->addWidget(newButton);
    updateStyleSheet();
}

//update button's stylesheet
void NewPYFlashListPrivate::updateButtonList()
{
    /*
    border-image: url(:/images/images/list_left_1.png);
    border-image: url(:/images/images/list_left_2.png);
    border-image: url(:/images/images/list_left_click.png);
    border-image: url(:/images/images/list_left_hove.png);
    */

    QString sender = QObject::sender()->objectName();
    int i=0;
    foreach(QPushButton* button,buttonList)
    {
        if(i%2 == 0)
        {
            button->setStyleSheet("border-image: url(:/images/images/list_left_1.png);color:white;");
        }
        else
        {
            button->setStyleSheet("border-image: url(:/images/images/list_left_2.png);color:white;");
        }

        if(button->objectName() == sender)
        {
            button->setStyleSheet("border-image: url(:/images/images/list_left_click.png);color:white;");
            emit sig_itemClicked(i);
            emit sig_itemClicked(button->text());
        }
        ++i;
    }
}

void NewPYFlashListPrivate::clear()
{
    foreach(QPushButton* button,buttonList)
    {
        delete button;
        button = NULL;
    }
    buttonList.clear();
}

void NewPYFlashListPrivate::render()
{
    update();
}

void NewPYFlashListPrivate::setItemHeight(int hei)
{
    buttonHeight=hei;
}

void NewPYFlashListPrivate::setCurrentIndex(int curIndex)
{

}

void NewPYFlashListPrivate::updateStyleSheet()
{
    int i=0;
    foreach(QPushButton* button,buttonList)
    {
        if(i%2 == 0)
        {
            button->setStyleSheet("border-image: url(:/images/images/list_left_1.png);color:white;");
        }
        else
        {
            button->setStyleSheet("border-image: url(:/images/images/list_left_2.png);color:white;");
        }

        if(i==0)
        {
            button->setStyleSheet("border-image: url(:/images/images/list_left_click.png);color:white;");
            emit sig_itemClicked(i);
            emit sig_itemClicked(button->text());
        }
        ++i;
    }
}
