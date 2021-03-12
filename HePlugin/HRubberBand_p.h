#pragma once

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

