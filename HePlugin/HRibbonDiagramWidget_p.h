#ifndef HRIBBONDIAGRAMWIDGET_P_H
#define HRIBBONDIAGRAMWIDGET_P_H

#include "HRibbonDiagramWidget.h"
#include "HCartesianWidget_p.h"

class HRibbonDiagramWidgetPrivate : public HCartesianWidgetPrivate
{
    Q_DECLARE_PUBLIC(HRibbonDiagramWidget)

public:
     HRibbonDiagramWidgetPrivate(HRibbonDiagramWidget *q);

public:
     QPixmap pixmapRibbon;
     QPolygonF polyRibbon;
};


#endif // HRIBBONDIAGRAMWIDGET_P_H
