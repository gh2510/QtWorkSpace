#ifndef LISTWIDGETGRAM_H
#define LISTWIDGETGRAM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QPaintEvent>
#include "ListButton.h"


class ListWidgetGram :public QWidget
{
    Q_OBJECT
public :
    explicit ListWidgetGram(QWidget * parent=0);
    ~ListWidgetGram();
    void translatelanguage();
signals:

    void turnpage(int current_page);
public slots:
    void turnpage(QString current_page);

private:
    void paintEvent(QPaintEvent *);
    QPoint press_point;
    bool is_move;
   QVBoxLayout *button_layout;
   QSignalMapper * signal_mapper;

    QList<ListButton *> button_list;
};


#endif // LISTWIDGETGRAM_H
