#include "attemperpage.h"
#include "ui_attemperpage.h"


AttemperPage::AttemperPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttemperPage)
{
    ui->setupUi(this);
}

AttemperPage::~AttemperPage()
{
    delete ui;
}
