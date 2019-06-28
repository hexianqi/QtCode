#ifndef HCIRCLECIRCULAR_P_H
#define HCIRCLECIRCULAR_P_H

#include "HCircleCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCircleCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCLECIRCULAR_P_H
