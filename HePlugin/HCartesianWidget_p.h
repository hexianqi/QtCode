#ifndef HCARTESIANWIDGET_P_H
#define HCARTESIANWIDGET_P_H

#include "HCartesianWidget.h"
#include "HDiagramWidget_p.h"

class HCartesianWidgetPrivate : public HDiagramWidgetPrivate
{
    Q_DECLARE_PUBLIC(HCartesianWidget)

public:
    HCartesianWidgetPrivate(HCartesianWidget *q);

public:
    HCartesianZoom *zoom;
    HCartesianCoordinate *coordinate;
    QAction *actionResetCoordinate;
    bool unitInRuler;
    QString unitX;
    QString unitY;
};

#endif // HCARTESIANWIDGET_P_H
