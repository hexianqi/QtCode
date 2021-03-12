#pragma once

#include "HQuality.h"

HE_DATA_BEGIN_NAMESPACE

class HQualityPrivate
{
public:
    HQualityPrivate();

public:
    IQualityItemCollection *damages = nullptr;
    IQualityItemCollection *criterions = nullptr;
    QMap<int, QColor> colors;
};

HE_DATA_END_NAMESPACE
