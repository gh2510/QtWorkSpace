#ifndef BARCHART_H
#define BARCHART_H

#include <qwt_plot.h>
#include <qstringlist.h>

class DistroChartItem;

class BarChart: public QwtPlot
{
    Q_OBJECT

public:
    BarChart( QWidget * = NULL );

public Q_SLOTS:
    void setOrientation( int );
    void exportChart();

private:
    void populate();

    DistroChartItem *d_barChartItem;//自定义直方图类
    QStringList d_distros;//改变方向重置标题用
};
#endif // BARCHART_H
