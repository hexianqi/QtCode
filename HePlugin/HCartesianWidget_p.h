#ifndef HCARTESIANWIDGET_P_H
#define HCARTESIANWIDGET_P_H

#include "HCartesianWidget.h"
#include "HDiagramWidget_p.h"

class HRubberBand;

class HCartesianWidgetPrivate : HDiagramWidgetPrivate
{
    Q_DECLARE_PUBLIC(HCartesianWidget)

public:
    HCartesianWidgetPrivate(HCartesianWidget *q);

public:

    HRubberBand *rubberBand;

};

#endif // HCARTESIANWIDGET_P_H
