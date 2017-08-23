#ifndef MYPLOT_H
#define MYPLOT_H
#include "qwt/qwt_plot.h"
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_scale_draw.h"
#include "qwt/qwt_legend.h"
#include "qwt/qwt_legend_label.h"
#include "qwt/qwt_plot_layout.h"
#include "qwt/qwt_scale_widget.h"
#include "qwt/qwt_plot_canvas.h"
#include <QDateTime>

#include <QMap>

#define HISTORY 60 // 设定显示时间跨度

//时间刻度表
class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw( const QTime &base ):
        baseTime( base )
    {
    }
    virtual QwtText label( double v ) const
    {
        QTime upTime = baseTime.addSecs( static_cast<int>( v ) );
        return upTime.toString();
    }

private:
    QTime baseTime;
};

//曲线
class MyCurve: public QwtPlotCurve
{
public:
    MyCurve( const QString &title ):
        QwtPlotCurve( title )
    {
        setRenderHint( QwtPlotItem::RenderAntialiased );//设置渲染效果，抗锯齿
    }

    void setColor( const QColor &color )
    {
        QColor c = color;
        //c.setAlpha( 150);//设置Alpha通道颜色
        c.setAlpha(255);//设置Alpha通道颜色 yangmeng
        setPen( c );//设置画笔
        //setBrush( c );//设置笔刷
    }

};

//实时曲线图
class MyPlot : public QwtPlot
{
    Q_OBJECT
public:

    MyPlot( QWidget * = 0 );
    ~MyPlot();

    void setymaxvalue(double yMaxValue=100){
        ymaxvalue=yMaxValue;
    }
    void init_plot();

    QwtLegend *mylegend;

public slots:
    void updateData(QString swtich_name,double cpuusage=0,double memusage=0,double delay=0);
    void setCurrentSwitchNumber(QString name);
    void  updateOther(QString switch_name,double in_sum,double out_sum);

private:
    QString currentswitchname;
    int switch_num;

   // double cpuusagearray[HISTORY];
   // double memusagearray[HISTORY];

    QStringList switchaddress;
    QMap<QString,double> switchSum;// 保存交换机总帶宽
    QMap<QString,double *>   cpuusagearray_map;
    QMap<QString,double *>   memusagearray_map;
    QMap<QString,double *>   caparray_map;
    QMap<QString,double *>   otherarray_map;
    QMap<QString,double *>   delay_map;

    MyCurve *cpucurve;
    MyCurve *memcurve;
   MyCurve *capcurve;
   MyCurve *othercurve;
   MyCurve *delaycurve;

    QTime starttime, cur_time;

    int time_calibration;//时间校准间隔
    double ymaxvalue;
    double timeData[HISTORY];
    QwtPlotCanvas *canvas;
    TimeScaleDraw *timescaldraw;
   QwtScaleWidget *scaleWidget ;


   void freshData();         //切换到当前交换机页面时，使用当前的数据刷新显示       yangmeng 161028
};

#endif // MYPLOT_H
