#ifndef LABELEDIT_H
#define LABELEDIT_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>

#include <QLineEdit>


#define SE_RECT_RADIUS 5
#define SE_EDIT_HEIGHT 27
#define SE_HEIGHT 30
#define SE_PEN_WIDTH 3
#define SE_LEFT_SPACE 10
#define SE_WIDGET_SPACE 3
#define SE_TOP 3

#define SE_BG_BRUSH_COLOR Qt::white
#define SE_BG_PEN_COLOR QColor(0,139,209)

class LabelEdit : public QWidget
{
    Q_OBJECT
public:
    explicit LabelEdit(QWidget *parent = 0);
    ~LabelEdit();
    void setLabel(const QString& str);
    void clear();

    void setLabelWidth(int width);
    void setEditWidth(int width);

    QString text() const;
    //重写父类方法
    void resizeEvent(QResizeEvent *);

    void paintEvent(QPaintEvent *);

    void enterEvent(QEvent *);

    void leaveEvent(QEvent *);

    void setEditDisabled(bool);
    void setEditReadOnly(bool);

    QSize sizeHint() const
    {
        return QSize(250,40);
    }

public slots:
    void setText(const QString str);

private:
    void drawBackground(QPainter* paitner);

private:
    void calcGeo();
    void initVariables();
    void initWidgets();

private:
   QLabel* m_label;
   QLineEdit* m_edit;

};


#endif // LABELEDIT_H
