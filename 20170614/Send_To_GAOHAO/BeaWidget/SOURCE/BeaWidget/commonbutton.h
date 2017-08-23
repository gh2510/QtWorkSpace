#ifndef COMMONBUTTON_H
#define COMMONBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>


class commonButton : public QWidget
{
    Q_OBJECT

public:
    explicit commonButton(QWidget *parent = 0);
    ~commonButton();

    void setWidth(int width);
    void setText(QString text);
signals:
    void click();

private:
    QPushButton *pushBtn;
    QVBoxLayout *main_layout;
};

#endif // COMMONBUTTON_H
