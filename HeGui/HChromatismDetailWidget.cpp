#include "HChromatismDetailWidget_p.h"
#include "HChromatismEditWidget.h"
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HChromatismDetailWidget::HChromatismDetailWidget(QWidget *parent) :
    HAbstractDataDetailWidget<IChromatism>(*new HChromatismDetailWidgetPrivate, parent)
{
    init();
}

HChromatismDetailWidget::~HChromatismDetailWidget()
{
    qDebug() << __func__;
}

void HChromatismDetailWidget::initialize(QVariantMap /*param*/)
{
}

QString HChromatismDetailWidget::typeName()
{
    return "HChromatismDetailWidget";
}

void HChromatismDetailWidget::init()
{
    Q_D(HChromatismDetailWidget);
    d->widget = new HChromatismEditWidget;
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(d->widget);
}

HE_GUI_END_NAMESPACE
