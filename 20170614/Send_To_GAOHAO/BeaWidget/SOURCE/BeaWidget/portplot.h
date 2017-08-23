#ifndef PORTPLOT_H
#define PORTPLOT_H
#include <myplot.h>
#include "qwt/qwt_plot.h"
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_scale_draw.h"
#include "qwt/qwt_legend.h"
#include "qwt/qwt_legend_label.h"
#include <QDateTime>
#include <QMap>
#define HISTORY 60 // 设定显示时间跨度
//时间刻度表

class PortPlot : public QwtPlot
{
    Q_OBJECT
public:


    PortPlot( QWidget * = 0 );
    ~PortPlot();
    void setymaxvalue(double yMaxValue=100)
    {
        ymaxvalue=yMaxValue;
    }
    void setcurrentportnumber(int i=1)
    {
         currentportnumber=i;
          setTitle("端口"+QString::number (currentportnumber+1)+"  in:"+QString::number (0)+"  out:"+QString::number (0));
        // setTitle("端口"+QString::number (currentportnumber+1)+"  峰值:"+" "+"  最小值:");
    }

    void init_plot();
    QwtLegend *portlegend;
    QwtPlotCanvas *canvas;
    TimeScaleDraw *timescaldraw;
    QwtScaleWidget *scaleWidget ;
public slots:
    void updateData(QString name,double in=0,double out=0);
    void setCurrentSwitchNumber(QString name);
signals:

private:
    int currentportnumber;
    QString currentswitchname;
    QStringList switchaddress;
    QMap<QString,double*>inarray_map;
    QMap<QString,double*>outarray_map;
    MyCurve *incurve;
    MyCurve *outcurve;
    QTime starttime;
    int time_calibration;//时间校准间隔

    double ymaxvalue;
    double timeData[HISTORY];
};

#endif // PORTPLOT_H
