#ifndef HABSTRACTACTIONSTRATEGY_P_H
#define HABSTRACTACTIONSTRATEGY_P_H

#include "HAbstractActionStrategy.h"
#include <QtCore/QSet>

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractActionStrategyPrivate
{
public:
    QSet<HActionType> actionSupport;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTACTIONSTRATEGY_P_H
