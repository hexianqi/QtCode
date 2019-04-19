#ifndef HSPECFITTING_P_H
#define HSPECFITTING_P_H

#include "HSpecFitting.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate : public HAbstractDataItemPrivate
{
public:
    QPolygonF fittingPoints;
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_P_H
