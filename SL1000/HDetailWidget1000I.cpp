#include "HDetailWidget1000I_p.h"
#include "ui_HDetailWidget1000I.h"

HDetailWidget1000I::HDetailWidget1000I(QWidget *parent) :
    HAbstractTestDetailWidget(*new HDetailWidget1000IPrivate, parent),
    ui(new Ui::HDetailWidget1000I)
{
    ui->setupUi(this);
}

HDetailWidget1000I::~HDetailWidget1000I()
{
    delete ui;
}
