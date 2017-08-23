#ifndef MYGRAPHICSPIXMAPITEM_H
#define MYGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QContextMenuEvent>
class MyGraphicsPixmapItem :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    MyGraphicsPixmapItem();
    MyGraphicsPixmapItem(QString &name_t);
    void setPixName(QString & name_t);
    QString getPixName();

signals:

    void nodeIsMoving(QPointF &pos);
    void nodeIsPressed();


private:
      QString pix_name;
};

#endif // MYGRAPHICSPIXMAPITEM_H
