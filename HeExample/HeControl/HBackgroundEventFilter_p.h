#pragma once

#include "HBackgroundEventFilter.h"
#include "HAbstractMouseEventFilter_p.h"

HE_BEGIN_NAMESPACE

class HBackgroundEventFilterPrivate : public HAbstractMouseEventFilterPrivate
{
public:
    HBackgroundEventFilterPrivate();

public:
    int index = 0;
    QStringList imageFile;
    bool repeated = true;  // 平铺
    bool stretched = false; // 拉伸
};

HE_END_NAMESPACE
