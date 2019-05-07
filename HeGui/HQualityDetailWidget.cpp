#include "HQualityDetailWidget_p.h"
#include "HQualityEditWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQualityDetailWidget::HQualityDetailWidget(QWidget *parent) :
    HAbstractDataDetailWidget<IQuality>(*new HQualityDetailWidgetPrivate, parent)
{
    init();
}

HQualityDetailWidget::~HQualityDetailWidget()
{
    qDebug() << __func__;
}

void HQualityDetailWidget::initialize(QVariantMap /*param*/)
{
}

QString HQualityDetailWidget::typeName()
{
    return "HQualityDetailWidget";
}

void HQualityDetailWidget::init()
{
    Q_D(HQualityDetailWidget);
    d->widget = new HQualityEditWidget;
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(d->widget);
}

HE_GUI_END_NAMESPACE
