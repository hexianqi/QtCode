#ifndef HCARTESIANWIDGET_P_H
#define HCARTESIANWIDGET_P_H

#include "HCartesianWidget.h"
#include "HDiagramWidget_p.h"

class HCartesianWidgetPrivate : public HDiagramWidgetPrivate
{
public:
    HCartesianWidgetPrivate(HCartesianWidget *q);

public:
    HCartesianZoom *zoom;
    HCartesianCoordinate *coordinate;
    bool unitInRuler = true;
    QString unitX;
    QString unitY;
};

#endif // HCARTESIANWIDGET_P_H
