#ifndef NEWPYFLASHLISTPRIVATE_H
#define NEWPYFLASHLISTPRIVATE_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
class QPushButton;

#define ITEM_START_ANGLE 270
#define ITEM_D_ANGLE 2
#define ITEM_D_ZOOMING_FACTOR 0.05
#define UPDATE_TIMER_INTERVAL 10 // ms
#define ITEM_COUNTER_TIMER_INTERVAL 200
#define SIZE_HINT QSize(300,300)

#define ITEM_HEIGHT 100
#define BG_START_COLOR QColor(89,89,89)
#define BG_END_COLOR QColor(90,90,90)

#define ITEM_START_COLOR ITEM_END_COLOR.lighter()
#define ITEM_END_COLOR QColor(62,135,166)

#define ITEM_START_COLOR_A ITEM_END_COLOR_A.lighter()
#define ITEM_END_COLOR_A QColor(221,221,221)

#define HOVER_OPACITY 0.2
#define HOVER_START_COLOR HOVER_END_COLOR.lighter()
#define HOVER_END_COLOR QColor(98,139,21)

#define HOVER_TEXT_COLOR Qt::white
#define SELECT_TEXT_COLOR Qt::red
#define NORMAL_TEXT_COLOR Qt::black

#define RECT_RADIUS 6

class ItemInfo
{
public:
    ItemInfo(const QString& str):m_strData(str),m_Angle(ITEM_START_ANGLE),m_ZoomingFactor(0){}
    ItemInfo():m_Angle(ITEM_START_ANGLE),m_ZoomingFactor(0){}
    ~ItemInfo(){}

public:
    /// public interfaces
    void setText(const QString& str)
    {
        m_strData = str;
    }

    QString getText() const
    {
        return m_strData;
    }

    void updateAngle()
    {
        m_Angle += ITEM_D_ANGLE;

        if(m_Angle >  360)
        {
            m_Angle = 0;
        }
    }

    void updateZoomingFactor()
    {
        m_ZoomingFactor += ITEM_D_ZOOMING_FACTOR;

        if(m_ZoomingFactor > 1.0)
        {
            m_ZoomingFactor = 1.0;
        }
    }

    bool jobDone() const
    {
        return m_Angle == 360 || m_ZoomingFactor == 1.0;
    }

    void resetAngle()
    {
        m_Angle = ITEM_START_ANGLE;
    }

    void resetZoomingFactor()
    {
        m_ZoomingFactor = 0.0;
    }

    qreal getAngle() const
    {
        return m_Angle;
    }

    qreal getZoomingFactor() const
    {
        return m_ZoomingFactor;
    }

    bool inWrongPosition() const
    {
        return m_Angle > ITEM_START_ANGLE && m_Angle < 360;
    }

    bool inWrongZoomingPosition()
    {
        return m_ZoomingFactor < 1.0;
    }

private:
    QString m_strData;
    qreal m_Angle;
    qreal m_ZoomingFactor;
};

namespace Ui {
class NewPYFlashListPrivate;
}

class NewPYFlashListPrivate : public QWidget
{
    Q_OBJECT

public:
    explicit NewPYFlashListPrivate(int hei,QWidget *parent = 0);
    ~NewPYFlashListPrivate();
    void addItem(const QString& str);
    void clear();
    void render();
    void setItemHeight(int hei);
    void updateStyleSheet();

public Q_SLOTS:
    void setCurrentIndex(int curIndex);
    void updateButtonList();

private:
    Ui::NewPYFlashListPrivate *ui;
    int buttonHeight;

    //add
    QPushButton* newButton;
    QList<QPushButton*> buttonList;

signals:
    void sig_setMaximum(int max);
    void sig_setCurrentIndex(int currIndex);
    void sig_itemClicked(const int& selectindex);
    void sig_itemClicked(const QString &text);
};

#endif // NEWPYFLASHLISTPRIVATE_H
