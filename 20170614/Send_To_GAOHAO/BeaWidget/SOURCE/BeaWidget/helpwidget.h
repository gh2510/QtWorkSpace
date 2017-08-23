#ifndef HELPWIDGET_H
#define HELPWIDGET_H
#include"commonbutton.h"
#include <QWidget>
#include <QLabel>

class HelpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HelpWidget(QWidget *parent = 0);

private:

    QLabel *lbl_help;

};

#endif // HELPWIDGET_H
