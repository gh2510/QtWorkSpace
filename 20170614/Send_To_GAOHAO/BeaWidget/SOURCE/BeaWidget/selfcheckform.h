#ifndef SELFCHECKFORM_H
#define SELFCHECKFORM_H

#include <QWidget>

namespace Ui {
class selfCheckForm;
}

class selfCheckForm : public QWidget
{
    Q_OBJECT

public:
    explicit selfCheckForm(QWidget *parent = 0);
    ~selfCheckForm();

private:
    Ui::selfCheckForm *ui;
};

#endif // SELFCHECKFORM_H
