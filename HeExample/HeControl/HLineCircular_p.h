#ifndef HLINECIRCULAR_P_H
#define HLINECIRCULAR_P_H

#include "HLineCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLineCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
};

HE_CONTROL_END_NAMESPACE

#endif // HLINECIRCULAR_P_H
