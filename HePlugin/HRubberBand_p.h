#ifndef HRUBBERBAND_P_H
#define HRUBBERBAND_P_H

#include "HRubberBand.h"
#include "HAbstractMouseStrategy_p.h"

class QRubberBand;

class HRubberBandPrivate : public HAbstractMouseStrategyPrivate
{
public:
    HRubberBandPrivate(QWidget *p);

public:
    QRubberBand *rubberBand;
    QPoint origin;
};

#endif // HRUBBERBAND_P_H
