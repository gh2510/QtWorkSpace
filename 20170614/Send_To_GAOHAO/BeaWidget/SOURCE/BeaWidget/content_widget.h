#ifndef CONTENT_WIDGET_H
#define CONTENT_WIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QPainter>
#include <QPen>
#include <QHBoxLayout>
#include <QEvent>
#include <QVBoxLayout>

class ContentWidget : public QWidget
{
    Q_OBJECT
    
public :
    explicit ContentWidget(QWidget *parent=0);
    void translateLanguage();
private :
    void initLeft();
    void initRightTop();
    void initRightCenter();
    void initRightCenterFunction();
    void initRightBottom();
    void initRight();
//protected:
//    bool eventFilter(QObject *obj,QEvent *event);
signals:
    void showLoginDialog();
    void showRegisterDialog();
private :
    QSplitter * main_splitter;
    QWidget * left_widget;
    QLabel * label;
    QLabel * suggest_label;
    QLabel * system_label;
    
    QPushButton *power_button;
    
    QSplitter * right_splitter;
    QWidget * right_widget;
    
    QWidget * right_top_widget;
    QPushButton * login_button;//login
    
    QWidget *right_center_widget;
    
    QWidget *right_center_function_widget;
    
    QWidget *right_bottom_widget;
    
};

#endif // CONTENT_WIDGET_H
