#include "captureform.h"
#include "ui_captureform.h"
#include<QDesktopWidget>
CaptureForm::CaptureForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaptureForm)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(54,54,54));  //background color
    palette.setColor(QPalette::WindowText,QColor("white"));
    int wi=QApplication::desktop()->width()*5/6;
    int hi=QApplication::desktop()->height()*5/6;
    setFixedSize(wi,hi);
    main_layout = new QVBoxLayout();
    captureWidget=new capturewidget();
    tabWidget=new QTabWidget(this);
    tabWidget->setFocusPolicy(Qt::NoFocus);
    tabWidget->setDocumentMode(true);
    tabWidget->setStyleSheet(
                "QTabBar::tab{ background: #77ac98; color: white; padding: 10px;border: 2px solid; } "
                "QTabBar::tab:selected { background: #007d65; white:red;font-size:12px;font-weight:bold;}"
                "QTabBar::tab:!selected {margin-top: 5px;}"
                );

    tabWidget->addTab(captureWidget,"当前镜像配置");
    main_layout->addStretch(1);
    main_layout->addWidget(tabWidget,0,Qt::AlignHCenter);
    main_layout->addStretch(1);
    this->setLayout(main_layout);
}

CaptureForm::~CaptureForm()
{
    delete ui;
    if(captureWidget) delete captureWidget;
    if(tabWidget)delete tabWidget;
    if(main_layout)delete main_layout;

}
