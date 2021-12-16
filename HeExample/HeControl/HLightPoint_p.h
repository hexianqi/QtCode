#pragma once
#include "HLightPoint.h"

HE_BEGIN_NAMESPACE

class HLightPointPrivate
{
public:
    int step = 10;
    QColor background = Qt::red;
    QTimer *timer = nullptr;
    int offset = 0;
    bool add = true;
};

HE_END_NAMESPACE
