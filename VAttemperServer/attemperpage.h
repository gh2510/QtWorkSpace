#ifndef ATTEMPERPAGE_H
#define ATTEMPERPAGE_H

#include <QWidget>

/*
 *类说明：界面类，负责读取配置文件的内容，完成战位和角色选择页面的显示。同时接收用户操作，启动调度引擎完成调度
 *创建人：高?
 *注意事项：本类默认读取运行程序同目录下的finalServer.xml文件
 *
 *
 */

namespace Ui {
class AttemperPage;
}

class AttemperPage : public QWidget
{
    Q_OBJECT
    
public:
    explicit AttemperPage(QWidget *parent = 0);
    ~AttemperPage();
    
private:
    Ui::AttemperPage *ui;
};

#endif // ATTEMPERPAGE_H
