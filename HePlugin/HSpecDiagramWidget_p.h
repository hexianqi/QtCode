#pragma once

#include "HSpecDiagramWidget.h"
#include "HRibbonDiagramWidget_p.h"

class HSpecDiagramWidgetPrivate : public HRibbonDiagramWidgetPrivate
{
public:
    HSpecDiagramWidgetPrivate();

public:
    bool drawCenter = false;
    bool drawTopLeft = true;
    QString textCenter;
    QString textTopLeft;
    QColor colorCenter = Qt::red;
    QColor colorTopLeft = Qt::blue;
    QFont fontCenter;
    QFont fontTopLeft;
    QBrush brushCenter;
};
