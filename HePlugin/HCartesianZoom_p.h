#ifndef HCARTESIANZOOM_P_H
#define HCARTESIANZOOM_P_H

#include "HCartesianZoom.h"
#include "HAbstractMouseStrategy_p.h"
#include <QtCore/QVector>

class QToolButton;
class HRubberBand;

class HCartesianZoomPrivate : public HAbstractMouseStrategyPrivate
{
public:
    HCartesianZoomPrivate(QWidget *);

public:
    int pos = 0;
    QToolButton *zoomIn = nullptr;
    QToolButton *zoomOut = nullptr;
    HRubberBand *rubberBand = nullptr;
    QVector<HCartesianCoordinate *> coordinates;
};

#endif // HCARTESIANZOOM_P_H
