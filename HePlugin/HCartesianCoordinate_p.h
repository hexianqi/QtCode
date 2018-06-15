#ifndef HCARTESIANCOORDINATE_P_H
#define HCARTESIANCOORDINATE_P_H

#include "HCartesianCoordinate.h"
#include <QRectF>

class HCartesianCoordinatePrivate
{
public:
    QRectF axis;
    int tickX;
    int tickY;
};

#endif // HCARTESIANCOORDINATE_P_H
