#include "selfcheckform.h"
#include "ui_selfcheckform.h"

selfCheckForm::selfCheckForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selfCheckForm)
{
    ui->setupUi(this);
}

selfCheckForm::~selfCheckForm()
{
    delete ui;
}
