#ifndef NEWLISTWIDGET_H
#define NEWLISTWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QToolButton>

namespace Ui {
class NewListwidget;
}

class NewListwidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewListwidget(QWidget *parent = 0);
    ~NewListwidget();
    void translatelanguage();

    void changeUser();      //改变用户角色 yangmeng 161022
    void setFirstPressed(int index);

signals:
    void turnpage(int current_page);

public slots:
    void turnpage();

private:
    Ui::NewListwidget *ui;
    QList <QToolButton *>button_list;

    void slot_WidgetShow(QString buttonName);
};

#endif // NEWLISTWIDGET_H
