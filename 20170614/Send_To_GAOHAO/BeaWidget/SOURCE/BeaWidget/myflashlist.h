#ifndef MYFLASHLIST_H
#define MYFLASHLIST_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollBar>

//#include "pyflashlistprivate.h"
#include "newpyflashlistprivate.h"

namespace Ui {
class myFlashList;
}

class myFlashList : public QWidget
{
    Q_OBJECT
public:
    explicit myFlashList(int hei,int num,QWidget *parent = 0);
    ~myFlashList();

public:
    /// proxy public interfaces for PYFlashListPrivate
    void addItem(const QString& str);
    void clear();
    void render();
    void set_item_height(int hei);

protected:
    QSize sizeHint() const
    {
        return QSize(SIZE_HINT);
    }
    void resizeEvent(QResizeEvent *);

private:
    /// private utility functoins
    void initVars();
    void initWgts();
    void initStgs();
    void initConns();
    void calcGeo();
    Ui::myFlashList *ui;

private Q_SLOTS:
    void setMaximum(int max);

private:
    QHBoxLayout* mainLayout;
    QScrollBar* scrollbar;
//    PYFlashListPrivate* PYFLP;
    NewPYFlashListPrivate *PYFLP;
    int m_item_height;

Q_SIGNALS:
    void sig_setCurrentIndex(int currIndex);
    void sig_itemClicked(const int &selectindex);
    void sig_itemClicked(const QString &text);

public slots:

};

#endif // MYFLASHLIST_H
