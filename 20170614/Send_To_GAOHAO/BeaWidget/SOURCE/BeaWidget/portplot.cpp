#include "portplot.h"
#include "qwt/qwt_scale_widget.h"
#include "qwt/qwt_plot_canvas.h"
#include "qwt/qwt_plot_layout.h"
#include "qwt/qwt_scale_widget.h"
#include"connection.h"
#include <QSqlQuery>
#include <QApplication>
#include <QDesktopWidget>
PortPlot::PortPlot(QWidget *parent):
    QwtPlot(parent)
{
    setymaxvalue(100);
    setFixedSize(QApplication::desktop()->width()*26/100,QApplication::desktop()->height()/3);
    setStyleSheet("font-size:11px;color:white;font-family:'wenquanyi'");

    init_plot();

    canvas=new QwtPlotCanvas(this);//画布
    if (canvas!=NULL){
        canvas->setStyleSheet("border-style: outset;border-width: 1px;border-radius: 10px;border-color:rgb(65,105,225);padding: 0px");

        setCanvas( canvas );//设置绘图的画布
    }
        plotLayout()->setAlignCanvasToScales( true );//设置对齐画布、坐标轴、刻度

        portlegend = new QwtLegend(this);//曲线描述
        portlegend->setFixedHeight(20);
        portlegend->setStyleSheet("border-style: outset;border-width: 0px;border-radius: 10px;background-color:rgb(25,25,25);padding: 0px");
        insertLegend( portlegend, QwtPlot::BottomLegend );//插入位置，可以分别是上下左右
//       // setAxisTitle( QwtPlot::xBottom, "时间\t[时:分:秒]" );//坐标轴标题-x轴
        starttime=QTime::currentTime ();//系统开始时间

        timescaldraw=new TimeScaleDraw( starttime.addSecs(-HISTORY));

        setAxisScaleDraw( QwtPlot::xBottom,timescaldraw);//设置x轴的刻度绘画
        setAxisScale( QwtPlot::xBottom, 0, HISTORY );//设置x轴坐标刻度大小
        setAxisLabelRotation( QwtPlot::xBottom, -50.0 );//标签旋转50度
        setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );
        scaleWidget = axisWidget( QwtPlot::xBottom );//x轴刻度控件
        const int fmh = QFontMetrics( scaleWidget->font() ).height();
        scaleWidget->setMinBorderDist( 0, fmh / 2 );//设置刻度的边界最小值，防止因为标签变化，引起跳动
        setAxisTitle( QwtPlot::xBottom, "端口流量Mbit/s" );//Y轴设置标题
       // setAxisTitle( QwtPlot::yLeft, "端口流量M/S" );//Y轴设置标题
        setAxisScale( QwtPlot::yLeft, 0, ymaxvalue);//Y轴刻度范围

        //timeData初始化
        incurve = new MyCurve( "in" );
        //    incurve->setBrush(QColor(88,188,60));
        incurve->setColor(  QColor(0,180,0,255)  );//设置曲线颜色
        incurve->attach( this );//插入plot

        outcurve = new MyCurve( "out" );
        //    outcurve->setBrush (QColor("gold"));
        outcurve->setColor(QColor(QColor(220,220,0,255)));
        outcurve->setZ(outcurve->z()+1 );//设置z轴上下先后顺序，哪个曲线在上。
        outcurve->attach( this );




}

void PortPlot::init_plot()
{

    QMap<QString,double*>::iterator it;
    for ( it = inarray_map.begin(); it != inarray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }


    for ( it = outarray_map.begin(); it != outarray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }
    inarray_map.clear();
    outarray_map.clear();
    switchaddress.clear();


    QSqlQuery query("",DBConnection::db);;
    query.exec ("select name from switch  order by  ID");
    int i=0;
    while (query.next ())
    {
        double *in_array=new double[HISTORY];
        for (int j=0;j<HISTORY;j++)
        {
            in_array[j]=0;
        }
        inarray_map.insert(query.value (0).toString (),in_array);

        double *out_array=new double[HISTORY];
        for (int j=0;j<HISTORY;j++)
        {
            out_array[j]=0;
        }
        outarray_map.insert(query.value (0).toString (),out_array);

        switchaddress<<query.value (0).toString ();
        i++;
    }
    if(switchaddress.size()>0)
    {
      currentswitchname=switchaddress.at(0);
    }
    currentportnumber=1;
    setTitle("端口"+QString::number (currentportnumber)+"  in:"+QString::number (0)+"  out:"+QString::number (0));
    //setTitle("端口"+QString::number (currentportnumber)+"  峰值:"+" "+"  最小值:");
    for ( int i = 0; i < HISTORY; i++ )
    {
        timeData[i] = i;
    }

    time_calibration=0;
    query.finish();
}


void PortPlot::updateData(QString  name,double in,double out)
{
    double max=0;
    if(name==currentswitchname)
        setTitle("端口"+QString::number (currentportnumber + 1)+"  in:"+QString::number (in,'f',4)+"  out:"+QString::number (out,'f',4));

    if(!inarray_map.keys().contains(name) || !outarray_map.keys().contains(name))
    {
        return;
    }
    for ( int i=0; i<HISTORY-1; i++ )//数组前移
    {       
       inarray_map[name][i]=inarray_map[name][i+1];
        outarray_map[name][i]=outarray_map[name][i+1];
    }
    inarray_map[name][HISTORY-1]=in;
    outarray_map[name][HISTORY-1]=out;
    if (name!=currentswitchname)
    {}
    else
    {
        if (time_calibration!=30)
        {
            int curTime = starttime.secsTo (QTime::currentTime ());
            for ( int j = 0; j < HISTORY; j++ )
            {  // timeData[j]++;
                timeData[j]=j+curTime;
            }
        }
        else
        {
            int curTime = starttime.secsTo (QTime::currentTime ());
            //timeData[j]=j+( starttime.secsTo (QTime::currentTime ()));
            for ( int j = 0; j < HISTORY; j++ )
            {
                timeData[j]=j+curTime;
                // timeData[j]=j+( starttime.secsTo (QTime::currentTime ()));
            }
            time_calibration=0;//每30秒重置为0
        }
            for(int i=0;i<HISTORY;i++)
            {
                if(max<inarray_map[currentswitchname][i])max=inarray_map[currentswitchname][i];
                if(max<outarray_map[currentswitchname][i])max=outarray_map[currentswitchname][i];
            }
            //  更改y轴的刻度
            max= ((max+100)/100);
            max=max*100*6/5;
            setymaxvalue(max);
            setAxisScale( QwtPlot::yLeft, 0, max);//Y轴刻度范围

            setAxisScale( QwtPlot::xBottom,timeData[0], timeData[HISTORY-1],0);//每次设置一下x轴刻度，起到递进变化效果
            incurve->setRawSamples (timeData, inarray_map[name],HISTORY);//每次更新一下曲线值
            outcurve->setRawSamples (timeData, outarray_map[name],HISTORY);
            replot();
            time_calibration++;
      }
}

void PortPlot::setCurrentSwitchNumber (QString name)
{
    currentswitchname=name;

}

PortPlot::~PortPlot()
{
    QMap<QString,double*>::iterator it;
    for ( it = inarray_map.begin(); it != inarray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }


    for ( it = outarray_map.begin(); it != outarray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }
    inarray_map.clear();
    outarray_map.clear();
    switchaddress.clear();
    delete incurve;
    incurve=NULL;
    delete outcurve;
    outcurve=NULL;
    if(portlegend)delete portlegend;
    if(canvas)delete canvas;
    if(timescaldraw)delete timescaldraw;
    if(scaleWidget)delete scaleWidget;
}




