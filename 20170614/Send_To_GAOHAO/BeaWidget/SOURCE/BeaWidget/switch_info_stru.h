#ifndef SWITCH_INFO_STRU_H
#define SWITCH_INFO_STRU_H
#include <QString>
#include <QPointF>
#include <QGraphicsView>
#include <QList>
#include "mygraphicspixmapitem.h"
#include "switchstateview.h"
class Switcher
{
private:
    QString  name;
    QString  IP;
    QString community;
    QPointF pos;
    QString  type;
    bool ports[SWITCH_NUM];
public:
    MyGraphicsPixmapItem *pix;
    QGraphicsTextItem   *text;
    QList<QGraphicsLineItem *> p_line_list;
    QStringList obj_swi_name_list;
    Switcher()
    {
        for(int i=0;i<SWITCH_NUM;i++)
            ports[i]=false;
    }
    ~Switcher()
    {

//        foreach (QGraphicsLineItem *item, p_line_list) {
//            delete item;
//            item=NULL;
//        }
    }
    void setPortState(int i,bool res)
    {
        ports[i]=res;
    }
    bool getPortState(int i)
    {
        return ports[i];
    }
 void setName(QString name)
 {
     this->name=name;
 }
  QString getName()
 {
      return this->name;
 }
  void setIp(QString IP)
  {
      this->IP=IP;
  }
  QString getIP()
  {
      return this->IP;
  }
  void setComunity(QString Comunity)
  {
      this->community=Comunity;
  }
  QString getComunity()
  {
      return this->community;
  }
  void setPos(float x,float y)
  {
      this->pos.setX(x);
      this->pos.setY(y);
  }
  void setPos(const QPointF f)
  {
      this->pos=f;
  }
  QPointF getPos()
  {
      return this->pos;
  }
  void setType(QString t)
  {
      type=t;
  }
  QString getType()
  {
      return type;
  }

};

#endif // SWITCH_INFO_STRU_H
