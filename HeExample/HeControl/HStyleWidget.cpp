#include "HStyleWidget_p.h"
#include "ui_HStyleWidget.h"
#include "HStyleFactory.h"
#include "ICustomStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

HStyleWidget::HStyleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HStyleWidget),
    d_ptr(new HStyleWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HStyleWidget::~HStyleWidget()
{
    delete ui;
}

void HStyleWidget::init()
{
    auto factory = new HStyleFactory(this);
    auto style = factory->createStyle("HFlatStyle");
    this->setStyleSheet(style->toStyleSheet());
}

HE_CONTROL_END_NAMESPACE
