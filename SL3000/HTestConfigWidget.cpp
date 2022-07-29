#include "HTestConfigWidget_p.h"
#include "ui_HTestConfigWidget.h"

HTestConfigWidget::HTestConfigWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTestConfigWidgetPrivate),
    ui(new Ui::HTestConfigWidget)
{
    ui->setupUi(this);
    initialize();
}

HTestConfigWidget::~HTestConfigWidget()
{
    delete ui;
}

void HTestConfigWidget::initialize()
{

}
