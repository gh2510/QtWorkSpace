#ifndef LOOPVIEW_H
#define LOOPVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QPaintEvent>
#include <QList>
#include <QString>
#include <QPainter>
class LoopView : public QWidget
{
    Q_OBJECT
public:
    explicit LoopView(QWidget *parent = 0);
    ~LoopView();

    void addText(const QString &newText);
    QString getText(int i) const;    
    virtual void paintEvent(QPaintEvent* e);

 protected:

       virtual void timerEvent(QTimerEvent* e);
       virtual void showEvent(QShowEvent* e);
       virtual void hideEvent(QHideEvent* e);

signals:

public slots:
private:

    void init_loop();
    int offset;
    int myTimerId;

    QStringList m_list_showtext;
};

#endif // LOOPVIEW_H
