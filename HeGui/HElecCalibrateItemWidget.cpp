#include "HElecCalibrateItemWidget_p.h"

HE_BEGIN_NAMESPACE

HElecCalibrateItemWidget::HElecCalibrateItemWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HElecCalibrateItemWidgetPrivate)
{
}

HElecCalibrateItemWidget::HElecCalibrateItemWidget(HElecCalibrateItemWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HElecType HElecCalibrateItemWidget::type()
{
    return d_ptr->type;
}

int HElecCalibrateItemWidget::gears()
{
    return d_ptr->gears;
}

void HElecCalibrateItemWidget::setData(IElecCalibrateItem *p, HElecType type, int gears)
{
    d_ptr->data = p;
    d_ptr->type = type;
    d_ptr->gears = gears;
    showData();
}

void HElecCalibrateItemWidget::setLoop(bool /*b*/)
{

}

void HElecCalibrateItemWidget::updateData(double /*value*/)
{

}

HE_END_NAMESPACE
