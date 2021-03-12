#pragma once

#include "HCartesianCoordinate.h"
#include <QtCore/QRectF>

class HCartesianCoordinatePrivate
{
public:
    QRectF axis;
    int tickX;
    int tickY;
};
