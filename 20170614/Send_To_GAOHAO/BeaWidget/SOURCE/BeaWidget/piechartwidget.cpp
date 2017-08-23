
#include "qchartviewer.h"
#include "chartdir.h"
#include "FinanceChart.h"
#include "piechartwidget.h"
PieChartWidget::PieChartWidget(QWidget *parent) :
    QWidget(parent)
{
     Chart::setLicenseCode("SXZVFNRN9MZ9L8LGA0E2B1BB");
    viewer=new QChartViewer(this);
     const char *imageMap = 0;
    double data[] = {35, 30, 25, 7, 6, 5, 4, 3, 2, 1};

      const char *labels[] = {"电压过高", "CPU过高", "温度过高", "内存过高", "硬盘空间不足",
        "Legal", "Insurance", "Licenses", "Transport", "Interest"};

    pie = new PieChart(680, 450, 0xabc88b);
    pie->setDefaultFonts("simsun.ttf","simsun.ttf");
    pie->addTitle("Project Cost Breakdown", "timesbi.ttf", 15)->setBackground(
        Chart::metalColor(0xb7ba6b));

   pie->setPieSize(300, 200, 110);

    pie->set3D(30);

   pie->setLabelLayout(Chart::SideLayout);

     TextBox *t = pie->setLabelStyle();
    t->setBackground(Chart::SameAsMainColor, Chart::Transparent, Chart::glassEffect()
        );
    t->setRoundedCorners(5);

    pie->setLineColor(Chart::SameAsMainColor, 0x000000);

    pie->setStartAngle(135);

    // Set the pie data and the pie labels
    pie->setData(DoubleArray(data, (int)(sizeof(data) / sizeof(data[0]))), StringArray(
        labels, (int)(sizeof(labels) / sizeof(labels[0]))));

    pie->makeChart("11.png");

    imageMap = pie->getHTMLImageMap("clickable", "",
        "title='{label}: US${value}K ({percent}%)'");


    viewer->setChart(pie);
    viewer->setImageMap(imageMap);

    viewer->show();
}
