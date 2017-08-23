#include "barchart.h"
#include <qwt_plot_renderer.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>

class DistroScaleDraw: public QwtScaleDraw
{
public:
    DistroScaleDraw( Qt::Orientation orientation, const QStringList &labels ):
        d_labels( labels )
    {
        setTickLength( QwtScaleDiv::MinorTick, 0 );
        setTickLength( QwtScaleDiv::MediumTick, 0 );
        setTickLength( QwtScaleDiv::MajorTick, 2 );

        enableComponent( QwtScaleDraw::Backbone, false );

        if ( orientation == Qt::Vertical )
        {
            setLabelRotation( -60.0 );
        }
        else
        {
            setLabelRotation( -20.0 );
        }

        setLabelAlignment( Qt::AlignLeft | Qt::AlignVCenter );
    }

    //刻度标签值
    virtual QwtText label( double value ) const
    {
        QwtText lbl;

        const int index = qRound( value );//四舍五入
        if ( index >= 0 && index <= d_labels.size() )
        {
            lbl = d_labels[ index ];
        }
        return lbl;
    }

private:
    const QStringList d_labels;
};

//直方图
//QwtPlotBarChart将一系列数据显示为bar
class DistroChartItem: public QwtPlotBarChart
{
public:
    DistroChartItem():
        QwtPlotBarChart( "Page Hits" )
    {
        setLegendMode( QwtPlotBarChart::LegendBarTitles );//显示所有bar各自的标题，而QwtPlotBarChart::LegendChartTitle 显示这个表的标题
        setLegendIconSize( QSize( 10, 14 ) );
    }

    //分配颜色和标题给bar，并更新
    void addDistro( const QString &distro, const QColor &color )
    {
        d_colors += color;
        d_distros += distro;
        itemChanged();//Update the legend of the parent plot.
    }

    //自定义每个Bar
    virtual QwtColumnSymbol *specialSymbol(
        int index, const QPointF& ) const
    {


        QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
        symbol->setLineWidth( 1 );
        symbol->setFrameStyle( QwtColumnSymbol::Plain );//Raised

        QColor c( Qt::white );
        if ( index >= 0 && index < d_colors.size() )
            c = d_colors[ index ];

        symbol->setPalette( c );

        return symbol;
    }
    //自定义每个bar的标题
    virtual QwtText barTitle( int sampleIndex ) const
    {
        QwtText title;
        if ( sampleIndex >= 0 && sampleIndex < d_distros.size() )
            title = d_distros[ sampleIndex ];

        return title;
    }

private:
    QList<QColor> d_colors;
    QList<QString> d_distros;
};

BarChart::BarChart( QWidget *parent ):
    QwtPlot( parent )
{
    const struct
    {
        const char *distro;
        const int hits;
        QColor color;

    } pageHits[] =
    {
        { "Arch", 1114, QColor( "DodgerBlue" ) },
        { "Debian", 1373, QColor( "#d70751" ) },
        { "Fedora", 1638, QColor( "SteelBlue" ) },
        { "Mageia", 1395, QColor( "Indigo" ) },
        { "Mint", 3874, QColor( 183, 255, 183 ) },
        { "openSuSE", 1532, QColor( 115, 186, 37 ) },
        { "Puppy", 1059, QColor( "LightSkyBlue" ) },
        { "Ubuntu", 2391, QColor( "FireBrick" ) }
    };

    setAutoFillBackground( true );
    setPalette( QColor( "Linen" ) );

    //设置画布
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth( 2 );
    canvas->setFrameStyle( QFrame::Box | QFrame::Sunken );
    canvas->setBorderRadius( 10 );

    QPalette canvasPalette( QColor( "Plum" ) );
    canvasPalette.setColor( QPalette::Foreground, QColor( "Indigo" ) );
    canvas->setPalette( canvasPalette );

    setCanvas( canvas );

    setTitle( "DistroWatch Page Hit Ranking, April 2012" );

    d_barChartItem = new DistroChartItem();

    //数据源
    QVector< double > samples;

    for ( uint i = 0; i < sizeof( pageHits ) / sizeof( pageHits[ 0 ] ); i++ )
    {
        d_distros += pageHits[ i ].distro; //给标题赋值
        samples += pageHits[ i ].hits;//给数据赋值

        d_barChartItem->addDistro(
            pageHits[ i ].distro, pageHits[ i ].color );//更新颜色和标题
    }

    d_barChartItem->setSamples( samples );//更新数据

    d_barChartItem->attach( this );

    insertLegend( new QwtLegend() );

    setOrientation( 0 );
    setAutoReplot( false );
}

void BarChart::setOrientation( int o )
{
    const Qt::Orientation orientation =
        ( o == 0 ) ? Qt::Vertical : Qt::Horizontal;

    int axis1 = QwtPlot::xBottom;
    int axis2 = QwtPlot::yLeft;

    if ( orientation == Qt::Horizontal )
        qSwap( axis1, axis2 );

    d_barChartItem->setOrientation( orientation );//直方图方向
    d_barChartItem->setSpacing( 20 );//spacing 是两个样本之间的距离（两个直方图之间的距离，或者每组直方图之间的距离
    d_barChartItem->setMargin( 30);// margin 最外层的直方图与画布的边框矩形之间的距离

    setAxisTitle( axis1, "Distros" );
    setAxisMaxMinor( axis1, 3);//设置坐标轴小刻度的最大值
    setAxisMaxMajor( axis1, 10);//设置坐标轴大刻度的最大值
    setAxisScaleDraw( axis1, new DistroScaleDraw( orientation, d_distros ) );//需要重新更新标题


    setAxisTitle( axis2, "Hits per day ( HPD )" );
    setAxisMaxMinor( axis2, 3 );

    QwtScaleDraw *scaleDraw = new QwtScaleDraw();
    scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 4 );
    setAxisScaleDraw( axis2, scaleDraw );

    plotLayout()->setCanvasMargin( 0 );
    replot();
}

void BarChart::exportChart()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( this, "distrowatch.pdf" );
}
