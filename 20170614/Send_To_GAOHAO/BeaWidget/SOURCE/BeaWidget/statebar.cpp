#include "statebar.h"


StateBar::StateBar(QWidget *parent) :
    QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    lbl_time=new QLabel();
    lbl_startTime=new QLabel();
    m_nTimerId = startTimer(1000);

    QPalette   pal;
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    lbl_time->setPalette(pal);
    lbl_startTime->setPalette(pal);
    QFont font3;
    font3.setFamily(QString::fromUtf8("Tahoma"));
    font3.setPointSize(11);
    font3.setBold(true);
    font3.setWeight(75);
    lbl_time->setFont(font3);
    lbl_startTime->setFont(font3);


    main_layout=new QVBoxLayout();
    main_layout->addStretch(1);
    main_layout->addWidget(lbl_time);
    main_layout->addWidget(lbl_startTime);
    main_layout->addStretch(1);
    setLayout(main_layout);
    //sTime.start();
    startTime=QDateTime::currentDateTime();
}

StateBar::~StateBar()
{
    if ( m_nTimerId != 0 )
        killTimer(m_nTimerId);
    if(lbl_time)delete lbl_time;
}

void StateBar::paintEvent(QPaintEvent * event)
{

}
void StateBar::timerEvent( QTimerEvent *event )
{
    time = QDateTime::currentDateTime();//获取系统现在的时间
    int runTime = startTime.secsTo(time);
    QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    lbl_time->setText("当前时间：" +  str);//在标签上显示时间
    QString day = QString::number(runTime/86400);
    lbl_startTime->setText("运行时间：" + day  + "天 " +QDateTime::fromTime_t(runTime).toUTC().toString("hh:mm:ss"));
}
