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
    HCartesianZoomPrivate(QWidget *p);

public:
    QToolButton *zoomIn;
    QToolButton *zoomOut;
    HRubberBand *rubberBand;
    QVector<HCartesianCoordinate *> coordinates;
    int pos;
};

#endif // HCARTESIANZOOM_P_H
