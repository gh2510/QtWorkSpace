#include "myplot.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSqlQuery>
#include<QDebug>
#include"connection.h"
MyPlot::MyPlot( QWidget *parent ):
    QwtPlot( parent )
{
//    setFixedSize(parent->width(),parent->height());
//    setFixedSize(QApplication::desktop()->width()-150,parent->height()-300);
    setymaxvalue(100);
    setStyleSheet("font-size:15px;color:white;font-family:'wenquanyi';");

    init_plot();

    canvas =new QwtPlotCanvas(this);//画布

    if (canvas!=NULL){
        canvas->setStyleSheet("border-style: outset;border-width: 1px;border-radius: 10px;border-color:rgb(65,105,225);padding: 0px"); 
        setCanvas( canvas );//设置绘图的画布
    }

    plotLayout()->setAlignCanvasToScales( true );//设置对齐画布、坐标轴、刻度

    mylegend = new QwtLegend(this);//曲线描述,图例
    mylegend->setFixedHeight (100);
    mylegend->setStyleSheet("border-style: outset;border-width: 0px;border-radius: 10px;background-color:rgb(25,25,25);padding: 0px");

    insertLegend( mylegend, QwtPlot::BottomLegend );//插入位置，可以分别是上下左右LeftLegend

    setAxisTitle( QwtPlot::xBottom, "时间\t[时:分:秒]" );//坐标轴标题-x轴
    starttime=QTime::currentTime ();//系统开始时间

    //性能曲线横轴修改 yangmeng 161022
    timescaldraw=new TimeScaleDraw( starttime.addSecs(-HISTORY));  //当前时间前150秒值已经初始化为0
    //timescaldraw=new TimeScaleDraw( starttime.addSecs(-150));  //当前时间前60秒值已经初始化为0

    setAxisScaleDraw( QwtPlot::xBottom,timescaldraw);//设置x轴的刻度绘画(wenben)
    //性能曲线横轴修改 yangmeng 161022
    setAxisScale( QwtPlot::xBottom, 0, HISTORY );//设置x轴坐标刻度大小,from 0 to 150
    //setAxisScale( QwtPlot::xBottom, 0, 150 );//设置x轴坐标刻度大小,from 0 to 60
    setAxisLabelRotation( QwtPlot::xBottom, -50.0 );//标签旋转50度
    setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );

    scaleWidget = axisWidget( QwtPlot::xBottom );//x轴刻度控件
    const int fmh = QFontMetrics( scaleWidget->font() ).height();
    scaleWidget->setMinBorderDist( 0, fmh / 2 );//设置刻度的边界最小值，防止因为标签变化，引起跳动
    setAxisTitle( QwtPlot::yLeft, "主要性能数据" );//Y轴设置标题
    setAxisScale( QwtPlot::yLeft, 0, ymaxvalue );//Y轴刻度范围



    //timeData初始化
    cpucurve = new MyCurve( "温度" );

    //    cpucurve->setBrush(QColor(88,188,60));
    //cpucurve->setColor( QColor(0,180,0,255) );//设置曲线颜色
    cpucurve->setColor( QColor(230,110,80,255) );       //yangmeng 161026 颜色统一 颜色调整
    cpucurve->attach( this );//插入plot


    capcurve=new MyCurve( "入带宽" );
    //    cpucurve->setBrush(QColor(88,188,60));
    //capcurve->setColor( QColor(200,140,10,255) );//设置曲线颜色
    capcurve->setColor( QColor(0,180,0,255) );       //yangmeng 161026 颜色统一
    capcurve->setZ(cpucurve->z()+1);//设置z轴上下先后顺序，哪个曲线在上。
    capcurve->attach( this );//插入plot

   // MyCurve * test2 = new MyCurve( "吞吐量" );
     //    cpucurve->setBrush(QColor(88,188,60));
     othercurve=new MyCurve( "出带宽" );
     //othercurve->setColor( QColor(225,30,220,255) );//设置曲线颜色
     othercurve->setColor(QColor(220,220,0,255));       //yangmeng 161026 颜色统一
     othercurve->setZ(capcurve->z()+1 );//设置z轴上下先后顺序，哪个曲线在上。
     othercurve->attach( this );//插入plot

     //取不到数据，暂时不显
    memcurve = new MyCurve( "内存" );
    //memcurve->setColor(QColor("blue"));
    memcurve->setColor(QColor(0, 220, 220, 255));        //yangmeng 161026 颜色调整
    memcurve->setZ(othercurve->z()+1 );//设置z轴上下先后顺序，哪个曲线在上。
    memcurve->attach( this );

    delaycurve = new MyCurve( "管理查询延迟" );  ;
    //delaycurve->setColor(QColor(220,220,0,255));
    delaycurve->setColor( QColor(225,30,220,255) );       //yangmeng 161026 颜色统一
    delaycurve->setZ(memcurve->z()+1 );//设置z轴上下先后顺序，哪个曲线在上。
    delaycurve->attach( this );

}
void MyPlot::init_plot()
{
    QMap<QString,double*>::iterator it;
    for ( it = cpuusagearray_map.begin(); it != cpuusagearray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }


    for ( it = caparray_map.begin(); it != caparray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }

    for ( it = memusagearray_map.begin(); it != memusagearray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }
    for ( it = otherarray_map.begin(); it != otherarray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }
    for ( it = delay_map.begin(); it != delay_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }

    cpuusagearray_map.clear();
    memusagearray_map.clear();
    switchaddress.clear();
    otherarray_map.clear();
    caparray_map.clear();
    delay_map.clear();

    QSqlQuery  query("",DBConnection::db);
    query.exec (" select  name from switch order by ID ");//order by ID
    int i=0;
    while (query.next ())
    {
        if(query.value (0).toString ()=="H1"||query.value (0).toString ()=="H2")
            switchSum.insert(query.value (0).toString (),168);
        else  if(query.value (0).toString ()=="A1"||query.value (0).toString ()=="A2"||query.value (0).toString ()=="B1"||query.value (0).toString ()=="B2")
            switchSum.insert(query.value (0).toString (),88);
        else  switchSum.insert(query.value (0).toString (),64);
        double *cpu_array=new double[HISTORY];
        for (int j=0;j<HISTORY;j++)
        {
            cpu_array[j]=10;
        }
        cpuusagearray_map.insert(query.value (0).toString (),cpu_array);

        double *mem_array=new double[HISTORY];
        for (int j=0;j<HISTORY;j++)
        {
            mem_array[j]=20;
        }
        memusagearray_map.insert(query.value (0).toString (),mem_array);

        double *cap_array=new double[HISTORY];
        for (int j=0;j<HISTORY;j++)
        {
            cap_array[j]=30;
        }
        caparray_map.insert(query.value (0).toString (),cap_array);

        double *other_array=new double[HISTORY];
        for (int j=0;j<HISTORY;j++)
        {
            other_array[j]=40;
        }
        otherarray_map.insert(query.value (0).toString (),other_array);

        double *delay_array=new double[HISTORY];
        for (int j=0;j<HISTORY;j++)
        {
            delay_array[j]=50;
        }
        delay_map.insert(query.value (0).toString (),delay_array);

        switchaddress<<query.value (0).toString ();
        i++;
    }
    switch_num=i;
    if(switch_num>0)        //yangmeng 161025
    {
        currentswitchname=switchaddress.at(0);

        query.prepare (" select  description  from switch where name=? ");
        query.bindValue(0,switchaddress.at(0));
        query.exec();
        query.next();
    }
    //setTitle (currentswitchname);
    setTitle (query.value(0).toString());

    for ( int i = 0; i < HISTORY; i++ )
    {
        //timeData[i] = i*2.5;        //性能曲线横轴修改 yangmeng 161022
        timeData[i] = i;
    }
    //    cpucurve->setRawSamples (timeData,cpuusagearray[0],HISTORY);//每次更新一下曲线值
    //    memcurve->setRawSamples (timeData,memusagearray[0],HISTORY);
    //    //曲线初始化
    time_calibration=0;
    query.finish();
    query.clear();
}

void MyPlot::updateData(QString switchname,double cpuusage,double memusage,double delay)
{

    if(!cpuusagearray_map.keys().contains(switchname) || !memusagearray_map.keys().contains(switchname) ||  !delay_map.keys().contains(switchname))
    {
        return;
    }
    //数据循环左移一位，并将最新的值放入最后
    for ( int i=0; i<HISTORY-1; i++ )   //接收到就进行数据更新
    {

        cpuusagearray_map[switchname][i]=cpuusagearray_map[switchname][i+1];
        memusagearray_map[switchname][i]=memusagearray_map[switchname][i+1];
        delay_map[switchname][i]=delay_map[switchname][i+1];
    }
    delay=delay/10000.0;
    cpuusagearray_map[switchname][HISTORY-1]=cpuusage;
    memusagearray_map[switchname][HISTORY-1]=memusage;
    delay_map[switchname][HISTORY-1]=delay;

    if (switchname!=currentswitchname){} //如果和当前的交换机号不同，则不画出来，不做处理
    else
    {

        cpucurve->setTitle("温度:"+QString::number(cpuusage)+"度");
        memcurve->setTitle("内存:"+QString::number(memusage)+"%");
        delaycurve->setTitle("管理查询延迟:"+QString::number(delay, 'f', 2)+"ms");        //yangmeng 161031 规约为2位小数
        othercurve->setTitle("进带宽:"+QString::number(otherarray_map[switchname][HISTORY-1], 'f', 2)+"%");
        capcurve->setTitle("出带宽:"+QString::number(caparray_map[switchname][HISTORY-1], 'f', 2)+"%");
        if (time_calibration!=30)
        {
            int curTime = starttime.secsTo (QTime::currentTime ());  //获取系统现在的时间
            for ( int j = 0; j < HISTORY; j++ )
            {
                timeData[j]=j+curTime;
            }
//            for ( int j = 0; j < HISTORY; j++ )
//                //timeData[j]++;
//                timeData[j]+=2;   //性能曲线横轴修改 yangmeng 161022
       }
        else
        {  int curTime = starttime.secsTo (QTime::currentTime ());  //获取系统现在的时间
            for ( int j = 0; j < HISTORY; j++ )
            {
               timeData[j]=j+curTime;
               //timeData[j]=j*2.5+curTime;  //性能曲线横轴修改 yangmeng 161022
            }
            time_calibration=0;//每30秒重置为0
        }

        //setAxisScale( QwtPlot::xBottom,0, 59,0);
        setAxisScale( QwtPlot::xBottom,timeData[0], timeData[HISTORY-1],0);
        //setAxisScale( QwtPlot::xBottom,0,60,0);
       // setAxisScale( QwtPlot::xBottom,timeData[0], timeData[HISTORY-1],0);//每次设置一下x轴刻度，起到递进变化效果
        //每次更新一下曲线值
        cpucurve->setRawSamples (timeData,cpuusagearray_map[switchname],HISTORY);//cpu
        memcurve->setRawSamples (timeData, memusagearray_map[switchname],HISTORY);//内存
        capcurve->setRawSamples (timeData, caparray_map[switchname],HISTORY);//出帶宽
        othercurve->setRawSamples (timeData, otherarray_map[switchname],HISTORY);//进帶宽
        delaycurve->setRawSamples (timeData, delay_map[switchname],HISTORY);//延迟
        replot();
        time_calibration++;
    }
}

//切换到当前交换机页面时，使用当前的数据刷新显示       yangmeng 161028
void MyPlot::freshData()
{
        //每次更新一下曲线值
        cpucurve->setRawSamples (timeData,cpuusagearray_map[currentswitchname],HISTORY);//cpu
        memcurve->setRawSamples (timeData, memusagearray_map[currentswitchname],HISTORY);//内存
        capcurve->setRawSamples (timeData, caparray_map[currentswitchname],HISTORY);//出帶宽
        othercurve->setRawSamples (timeData, otherarray_map[currentswitchname],HISTORY);//进帶宽
        delaycurve->setRawSamples (timeData, delay_map[currentswitchname],HISTORY);//延迟

        cpucurve->setTitle("温度:"+QString::number(cpuusagearray_map[currentswitchname][HISTORY-1])+"度");
        memcurve->setTitle("内存:"+QString::number(memusagearray_map[currentswitchname][HISTORY-1])+"%");
        delaycurve->setTitle("管理查询延迟:"+QString::number(delay_map[currentswitchname][HISTORY-1], 'f', 2)+"ms");        //yangmeng 161031 规约为2位小数
        othercurve->setTitle("进带宽:"+QString::number(otherarray_map[currentswitchname][HISTORY-1], 'f', 2)+"%");
        capcurve->setTitle("出带宽:"+QString::number(caparray_map[currentswitchname][HISTORY-1], 'f', 2)+"%");
        replot();
}

void MyPlot::setCurrentSwitchNumber (QString name)
{
    QSqlQuery  query("",DBConnection::db);
    query.prepare (" select  description  from switch where name=? ");
    query.bindValue(0,name);
    query.exec();
    query.next();

    currentswitchname=query.value(0).toString().right(2);
    setTitle (query.value(0).toString());
    query.finish();
    query.clear();
    //点击list选中的列标号为从0开始，所以要加1

    freshData();
}

void MyPlot::updateOther(QString switch_name, double in_sum, double out_sum)
{
    if(!otherarray_map.keys().contains(switch_name)||!caparray_map.keys().contains(switch_name))
    {
        return;
    }
    //数据循环左移一位，并将最新的值放入最后
    for ( int i=0; i<HISTORY-1; i++ )   //接收到就进行数据更新
    {

        otherarray_map[switch_name][i]=otherarray_map[switch_name][i+1];
        caparray_map[switch_name][i]=caparray_map[switch_name][i+1];
    }
     otherarray_map[switch_name][HISTORY-1]=in_sum*100/(switchSum[switch_name]);
      caparray_map[switch_name][HISTORY-1]=out_sum*100/(switchSum[switch_name]);

}

MyPlot::~MyPlot()
{
    QMap<QString,double*>::iterator it;
    for ( it = cpuusagearray_map.begin(); it != cpuusagearray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }


    for ( it = caparray_map.begin(); it != caparray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }

    for ( it = memusagearray_map.begin(); it != memusagearray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }
    for ( it = otherarray_map.begin(); it != otherarray_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }
    for ( it = delay_map.begin(); it != delay_map.end(); ++it ) {
        double * tmp=it.value();
        delete[] tmp;
    }
    cpuusagearray_map.clear();
    memusagearray_map.clear();
    switchaddress.clear();
    otherarray_map.clear();
    caparray_map.clear();
    delay_map.clear();

    if(canvas) delete canvas;
    if(timescaldraw) delete timescaldraw;
    if(scaleWidget) delete scaleWidget;
    if(cpucurve) delete cpucurve;
    cpucurve=NULL;
    if(memcurve )delete memcurve;
    memcurve=NULL;
    if(capcurve) delete capcurve;
    cpucurve=NULL;
    if(othercurve )delete othercurve;
    memcurve=NULL;
    if(delaycurve )delete delaycurve;
    delaycurve=NULL;
}
