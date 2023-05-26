#include "HTestSetWidget1000I_p.h"
#include "ui_HTestSetWidget1000I.h"

HTestSetWidget1000I::HTestSetWidget1000I(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget1000IPrivate, parent),
    ui(new Ui::HTestSetWidget1000I)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget1000I::~HTestSetWidget1000I()
{
    delete ui;
}
