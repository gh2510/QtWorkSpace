#include "iconameter.h"
#include "chartdir.h"
#include "FinanceChart.h"
#include <QHBoxLayout>
iconameter::iconameter(QWidget *parent) :
    QWidget(parent)
{

    Chart::setLicenseCode("SXZVFNRN9MZ9L8LGA0E2B1BB");
    viewer=new QChartViewer();

    viewer->setChart(getIconChart(0));
   // viewer->show();
    QHBoxLayout mainlayout;
    mainlayout.addWidget(viewer);
    setLayout(&mainlayout);
}
BaseChart* iconameter::getIconChart(int value)
{
    // The value to display on the meter


    // Create an AugularMeter object of size 70 x 90 pixels, using black background
    // with a 2 pixel 3D depressed border.

    AngularMeter *m = new AngularMeter(50, 80, Chart::Transparent);
    // Use white on black color palette for default text and line colors
    m->setColors(Chart::greenMetalGradient);
    m->setBackground(Chart::metalColor(0xb7ba6b));

    // Set the meter center at (10, 45), with radius 50 pixels, and span from 135 to
    // 45 degress
    m->setMeter(5, 40, 30, 135, 45);

    // Set meter scale from 0 - 100, with the specified labels
    const char * pattern1[] = {"", " ", " ", " ", ""};
    m->setScale(0, 100, StringArray(pattern1, (int)(sizeof(pattern1) / sizeof(
        pattern1[0]))));

    // Set the angular arc and major tick width to 2 pixels
    m->setLineWidth(1, 1);

    // Add a red zone at 0 - 15
     m->addZone(0, 10, 0x1d953f);
     m->addZone(10, 20, 0x007947);
     m->addZone(20, 30, 0x84bf96);
     m->addZone(30, 40, 0xabc88b);
     m->addZone(40, 50, 0xd5c59f);
     m->addZone(50, 60, 0xcd9a5b);
     m->addZone(60, 70, 0xdf9464);
     m->addZone(70, 80, 0xf3715c);
     m->addZone(80, 90, 0xef4136);
     m->addZone(90, 100, 0xed1941);
    // Add an icon at (25, 35)
   // m->addText(25, 35, "<*img=gas.gif*>");

    // Add a yellow (ffff00) pointer at the specified value
    pmeter=m->addPointer(value, 0x77ac98);
    return m;

    // Output the chart
    //m->makeChart();

}
void iconameter::setMeterPos(double value)
{
    delete viewer->getChart();
    viewer->setChart(getIconChart(value));
}
