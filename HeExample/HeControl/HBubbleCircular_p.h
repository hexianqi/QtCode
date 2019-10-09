#ifndef HBUBBLECIRCULAR_P_H
#define HBUBBLECIRCULAR_P_H

#include "HBubbleCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HBubbleCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor foreground = QColor(24, 189, 155);
};

HE_CONTROL_END_NAMESPACE

#endif // HBUBBLECIRCULAR_P_H
