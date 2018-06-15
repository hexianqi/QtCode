#include "HVernierWidget_p.h"
#include "HVernierTracking.h"

HVernierWidgetPrivate::HVernierWidgetPrivate(HVernierWidget *q)
    : HCartesianWidgetPrivate(q)
{
}

HVernierWidget::HVernierWidget(QWidget *parent)
    : HCartesianWidget(*new HVernierWidgetPrivate(this), parent)
{
    init();
}

HVernierWidget::HVernierWidget(HVernierWidgetPrivate &p, QWidget *parent)
    : HCartesianWidget(p, parent)
{
    init();
}

HVernierWidget::~HVernierWidget()
{
}

HVernierTracking *HVernierWidget::tracking()
{
    Q_D(HVernierWidget);
    return d->tracking;

}

void HVernierWidget::init()
{
    Q_D(HVernierWidget);
    d->tracking = new HVernierTracking(Qt::Vertical, this);

}



