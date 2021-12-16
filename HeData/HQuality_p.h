#pragma once

#include "HQuality.h"

HE_BEGIN_NAMESPACE

class HQualityPrivate
{
public:
    HQualityPrivate();

public:
    IQualityItemCollection *damages = nullptr;
    IQualityItemCollection *criterions = nullptr;
    QMap<int, QColor> colors;
};

HE_END_NAMESPACE
