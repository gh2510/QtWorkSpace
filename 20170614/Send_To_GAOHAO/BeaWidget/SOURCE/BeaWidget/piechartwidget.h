#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>
#include "FinanceChart.h"
#include "qchartviewer.h"
class PieChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PieChartWidget(QWidget *parent = 0);

signals:

public slots:
private:
    QChartViewer *viewer;
    PieChart *pie;
};

#endif // PIECHARTWIDGET_H
