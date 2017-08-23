#ifndef ICONAMETER_H
#define ICONAMETER_H

#include <QWidget>
#include "qchartviewer.h"
class iconameter : public QWidget
{
    Q_OBJECT
public:
    explicit iconameter(QWidget *parent = 0);
      BaseChart * getIconChart(int value);
signals:

public slots:
      void setMeterPos(double value);
private:

    QChartViewer *viewer;
    MeterPointer *pmeter;
};

#endif // ICONAMETER_H
