#ifndef HABSTRACTDOMAIN_P_H
#define HABSTRACTDOMAIN_P_H

#include "HAbstractDomain.h"

class HAbstractDomainPrivate
{
public:
    double minX;
    double maxX;
    double minY;
    double maxY;
    bool signalsBlocked;
    bool zoomed;
    double zoomResetMinX;
    double zoomResetMaxX;
    double zoomResetMinY;
    double zoomResetMaxY;
};

#endif // HABSTRACTDOMAIN_P_H
