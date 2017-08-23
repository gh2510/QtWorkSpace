#include "mygraphicscene.h"

myGraphicScene::myGraphicScene(QObject *parent):QGraphicsScene(parent)
{
}
void myGraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //QPointF pos = event->scenePos();
    QPointF pos(event->scenePos().x()-beforePos.x(),event->scenePos().y()-beforePos.y());
    emit isMoving(pos);
    //qDebug()<<"x:"<<pos.x()<<"y:"<<pos.y();
}
void myGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    beforePos = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}
void myGraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    releasePos = event->scenePos();
    QGraphicsScene::mouseReleaseEvent(event);
}
