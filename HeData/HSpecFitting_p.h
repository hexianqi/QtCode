#ifndef HSPECFITTING_P_H
#define HSPECFITTING_P_H

#include "HSpecFitting.h"
#include "HAbstractCalibrateItem_p.h"
#include <QtGui/QPolygonF>

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate : public HAbstractCalibrateItemPrivate
{
public:
    QPolygonF fittingPoints;
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_P_H
