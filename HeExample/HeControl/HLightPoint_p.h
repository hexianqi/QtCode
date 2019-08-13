#ifndef HLIGHTPOINT_P_H
#define HLIGHTPOINT_P_H

#include "HLightPoint.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLightPointPrivate
{
public:
    int step = 10;
    QColor background = Qt::red;
    QTimer *timer = nullptr;
    int offset = 0;
    bool add = true;
};

HE_CONTROL_END_NAMESPACE

#endif // HLIGHTPOINT_P_H
