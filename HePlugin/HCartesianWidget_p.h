#pragma once

#include "HCartesianWidget.h"
#include "HDiagramWidget_p.h"

class HCartesianWidgetPrivate : public HDiagramWidgetPrivate
{
public:
    HCartesianZoom *zoom;
    HCartesianCoordinate *coordinate;
    bool unitInRuler = true;
    QString unitX;
    QString unitY;
};
