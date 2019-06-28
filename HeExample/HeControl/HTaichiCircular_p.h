#ifndef HTAICHICIRCULAR_P_H
#define HTAICHICIRCULAR_P_H

#include "HTaichiCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HTaichiCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor background = Qt::black;
    QColor foreground = Qt::white;
};

HE_CONTROL_END_NAMESPACE

#endif // HTAICHICIRCULAR_P_H
