#ifndef DATEEDIT_H
#define DATEEDIT_H


#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>
#include "calendar_dialog.h"
#define SE_RECT_RADIUS 5
#define SE_EDIT_HEIGHT 27
#define SE_HEIGHT 30
#define SE_PEN_WIDTH 3
#define SE_LEFT_SPACE 10
#define SE_WIDGET_SPACE 3
#define SE_TOP 3

#define SE_BG_BRUSH_COLOR Qt::white
#define SE_BG_PEN_COLOR QColor(0,139,209)
class DateEdit : public QWidget
{
    Q_OBJECT
public:
    explicit DateEdit(QWidget *parent = 0);
    ~DateEdit();
    void setText(const QString& str);
    void setLabel(const QString& str);
    void clear();

    QString text() const;
    QLineEdit* m_edit;

public slots:
  void showcalendar();
  void setdate(const QDate&);
protected:
    void resizeEvent(QResizeEvent *);

    void paintEvent(QPaintEvent *);

    void enterEvent(QEvent *);

    void leaveEvent(QEvent *);

    QSize sizeHint() const
    {
        return QSize(250,40);
    }
private:
    void drawBackground(QPainter* paitner);

private:
    void calcGeo();
    void initVariables();
    void initWidgets();

private:
    QLabel* m_label;
    QPushButton* m_checkdate;

    CalendarDialog *calendar;
    bool m_bEnter;


};

#endif // DATEEDIT_H
