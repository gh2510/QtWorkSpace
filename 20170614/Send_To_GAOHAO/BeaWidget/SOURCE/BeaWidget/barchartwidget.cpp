#include "barchartwidget.h"

#include "chartdir.h"
#include "FinanceChart.h"
BarChartWidget::BarChartWidget(QWidget *parent) :
    QWidget(parent)
{
    Chart::setLicenseCode("SXZVFNRN9MZ9L8LGA0E2B1BB");
    viewer=new QChartViewer(this);
    const char *imageMap = 0;
    double data[] = {85, 156, 179.5, 211, 123,500,2,33,42,54,64};

    // The labels for the bar chart
    const char *labels[] = {"Mon", "Tue", "Wed", "Thu", "Fri","cc","dd","ds","qg","dss","aaa"};

    // Create a XYChart object of size 400 x 240 pixels.
    XYChart *c = new XYChart(680, 450);

    // Add a title to the chart using 14 pts Times Bold Italic font

    c->addTitle("Project Cost Breakdown", "timesbi.ttf", 15)->setBackground(
        Chart::metalColor(0xb7ba6b));

    // Set the plotarea at (45, 40) and of 300 x 160 pixels in size. Use alternating
    // light grey (f8f8f8) / white (ffffff) background.
    c->setPlotArea(80, 80, 470, 280, 0xf8f8f8, 0xabc88b);

    // Add a multi-color bar chart layer
    BarLayer *layer = c->addBarLayer(DoubleArray(data, (int)(sizeof(data) / sizeof(
        data[0]))), IntArray(0, 0));

    // Set layer to 3D with 10 pixels 3D depth
    layer->set3D(10);

    // Set bar shape to circular (cylinder)
    layer->setBarShape(Chart::CircleShape);

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(labels, (int)(sizeof(labels) / sizeof(labels[0]
        ))));

    // Add a title to the y axis
    c->yAxis()->setTitle("MBytes");

    // Add a title to the x axis
    c->xAxis()->setTitle("Work Week 25");

    // Output the chart
    c->makeChart();

    //include tool tip for the chart
    imageMap = c->getHTMLImageMap("clickable", "",
        "title='{xLabel}: {value} MBytes'");
    viewer->setChart(c);
    viewer->setImageMap(imageMap);
    viewer->show();
}
