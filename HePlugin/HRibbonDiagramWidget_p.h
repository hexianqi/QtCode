#ifndef HRIBBONDIAGRAMWIDGET_P_H
#define HRIBBONDIAGRAMWIDGET_P_H

#include "HRibbonDiagramWidget.h"
#include "HCartesianWidget_p.h"

class HRibbonDiagramWidgetPrivate : public HCartesianWidgetPrivate
{
public:
     HRibbonDiagramWidgetPrivate();

public:
     QPixmap pixmapRibbon;
     QPolygonF polyRibbon;
     bool drawRibbon = true;
     QAction *actionRibbon = nullptr;
};

#endif // HRIBBONDIAGRAMWIDGET_P_H
