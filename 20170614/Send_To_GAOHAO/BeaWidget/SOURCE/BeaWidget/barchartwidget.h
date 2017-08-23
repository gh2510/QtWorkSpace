#ifndef BARCHARTWIDGET_H
#define BARCHARTWIDGET_H

#include <QWidget>
#include "qchartviewer.h"
class BarChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BarChartWidget(QWidget *parent = 0);

signals:

public slots:
private:
    QChartViewer *viewer;
};

#endif // BARCHARTWIDGET_H
