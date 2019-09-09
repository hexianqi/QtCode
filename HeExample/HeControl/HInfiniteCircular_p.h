#ifndef HINFINITECIRCULAR_P_H
#define HINFINITECIRCULAR_P_H

#include "HInfiniteCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HInfiniteCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor background = QColor(46, 194, 163);
    QColor foreground = QColor(255, 107, 107);
};

HE_CONTROL_END_NAMESPACE

#endif // HINFINITECIRCULAR_P_H
