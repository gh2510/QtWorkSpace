#ifndef LABELCOMBOX_H
#define LABELCOMBOX_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>

#include <QComboBox>


#define SE_RECT_RADIUS 5
#define SE_EDIT_HEIGHT 27
#define SE_HEIGHT 30
#define SE_PEN_WIDTH 3
#define SE_LEFT_SPACE 10
#define SE_WIDGET_SPACE 3
#define SE_TOP 3

#define SE_BG_BRUSH_COLOR Qt::white
#define SE_BG_PEN_COLOR QColor(0,139,209)

class LabelComBox : public QWidget
{
    Q_OBJECT
public:
    explicit LabelComBox(QWidget *parent = 0);
    ~LabelComBox();
    void addItem(const QString& str);
    void setLabel(const QString& str);
    void setIndex(int index);
    void clear();

    QString text() const;
    void resizeEvent(QResizeEvent *);

    void paintEvent(QPaintEvent *);

    void enterEvent(QEvent *);

    void leaveEvent(QEvent *);

    QSize sizeHint() const
    {
        return QSize(250,40);
    }

signals:
    void indexChanged(QString text);
private:
    void drawBackground(QPainter* paitner);

private:
    void calcGeo();
    void initVariables();
    void initWidgets();


private:
   QLabel* m_label;
   QComboBox* m_comb;

};

#endif // LABELCOMBOX_H
