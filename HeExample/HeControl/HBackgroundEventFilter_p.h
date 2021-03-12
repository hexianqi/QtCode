#pragma once

#include "HBackgroundEventFilter.h"
#include "HAbstractMouseEventFilter_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HBackgroundEventFilterPrivate : public HAbstractMouseEventFilterPrivate
{
public:
    HBackgroundEventFilterPrivate();

public:
    int index = 0;
    QStringList imageFiles;
    bool repeated = false;  // 平铺
    bool stretched = false; // 拉伸
};

HE_CONTROL_END_NAMESPACE
