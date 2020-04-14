#ifndef HSPECDIAGRAMWIDGET_P_H
#define HSPECDIAGRAMWIDGET_P_H

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

#endif // HSPECDIAGRAMWIDGET_P_H
