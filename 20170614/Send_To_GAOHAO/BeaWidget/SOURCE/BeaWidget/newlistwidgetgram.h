#ifndef NEWLISTWIDGETGRAM_H
#define NEWLISTWIDGETGRAM_H

#include <QWidget>
#include <QList>
class QToolButton;

namespace Ui {
class NewListWidgetGram;
}

class NewListWidgetGram : public QWidget
{
    Q_OBJECT

public:
    explicit NewListWidgetGram(QWidget *parent = 0);
    ~NewListWidgetGram();
    void translatelanguage();
    void turnToFirstPage();

signals:
    void turnpage(int current_page);

public slots:
    void turnpage();

private:
    Ui::NewListWidgetGram *ui;
    QList<QToolButton *> button_list;

    void slot_WidgetShow(QString buttonname);
};

#endif // NEWLISTWIDGETGRAM_H
