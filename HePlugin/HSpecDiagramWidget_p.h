#ifndef HSPECDIAGRAMWIDGET_P_H
#define HSPECDIAGRAMWIDGET_P_H

#include "HSpecDiagramWidget.h"
#include "HCartesianWidget_p.h"

class HSpecDiagramWidgetPrivate : public HCartesianWidgetPrivate
{
    Q_DECLARE_PUBLIC(HSpecDiagramWidget)

public:
    HSpecDiagramWidgetPrivate(HSpecDiagramWidget *q);

public:
    bool drawCenter = false;
    bool drawTopLeft = false;
    QString textCenter;
    QString textTopLeft;
    QColor colorCenter = Qt::red;
    QColor colorTopLeft = Qt::red;
    QFont fontCenter;
    QFont fontTopLeft;
    QBrush brushCenter;
};

#endif // HSPECDIAGRAMWIDGET_P_H
