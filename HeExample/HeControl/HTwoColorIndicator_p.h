#pragma once

#include "HTwoColorIndicator.h"

HE_BEGIN_NAMESPACE

class HTwoColorIndicatorPrivate
{
public:
    QColor foreground = Qt::black;
    QColor background = Qt::white;
    bool active = false;
    bool dragEnabled = false;
    QPoint pressPos;
    bool foregroundPress = false;
    bool backgroundPress = false;
};

HE_END_NAMESPACE
