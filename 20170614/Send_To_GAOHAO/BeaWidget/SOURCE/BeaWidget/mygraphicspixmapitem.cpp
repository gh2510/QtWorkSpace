#include "mygraphicspixmapitem.h"
#include <QCursor>
#include <QMenu>
#include <QAction>
#include<QMessageBox>
MyGraphicsPixmapItem::MyGraphicsPixmapItem()
{

}
MyGraphicsPixmapItem::MyGraphicsPixmapItem(QString& name_t)
{
   this->pix_name=name_t;
}
 void MyGraphicsPixmapItem::setPixName(QString& name_t)
{
    this->pix_name=name_t;
}
QString MyGraphicsPixmapItem::getPixName()
{
   return this->pix_name;
}



