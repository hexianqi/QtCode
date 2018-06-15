#ifndef HVERNIERWIDGET_P_H
#define HVERNIERWIDGET_P_H

#include "HVernierWidget.h"
#include "HCartesianWidget_p.h"

class HVernierWidgetPrivate : public HCartesianWidgetPrivate
{
    Q_DECLARE_PUBLIC(HVernierWidget)

public:
    HVernierWidgetPrivate(HVernierWidget *q);

public:
    HVernierTracking *tracking;

};

#endif // HVERNIERWIDGET_P_H
