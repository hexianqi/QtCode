#pragma once

#include "HPetalCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPetalCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor foreground = QColor(255, 0, 155);
};

HE_CONTROL_END_NAMESPACE
