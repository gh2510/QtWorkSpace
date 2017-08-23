#ifndef CAPTUREFORM_H
#define CAPTUREFORM_H

#include <QWidget>
#include<QVBoxLayout>
#include<QTabWidget>
#include<QScrollArea>
#include"capturewidget.h"
namespace Ui {
class CaptureForm;
}

class CaptureForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit CaptureForm(QWidget *parent = 0);
    ~CaptureForm();
    
private:
    Ui::CaptureForm *ui;
    QVBoxLayout *main_layout;
    QTabWidget *tabWidget;
    capturewidget  * captureWidget;
};

#endif // CAPTUREFORM_H
