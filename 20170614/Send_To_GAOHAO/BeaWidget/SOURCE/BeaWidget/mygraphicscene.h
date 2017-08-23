#ifndef MYGRAPHICSCENE_H
#define MYGRAPHICSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
class myGraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    myGraphicScene(QObject *parent = 0);
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void isMoving(QPointF &pos);

public slots:

private:
    QPointF  beforePos;
    QPointF  releasePos;
};

#endif // MYGRAPHICSCENE_H
