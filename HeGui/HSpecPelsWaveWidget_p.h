#pragma once

#include "HSpecPelsWaveWidget.h"
#include "HePlugin/HEntireTableWidget_p.h"

HE_BEGIN_NAMESPACE

class HSpecPelsWaveWidgetPrivate : public HEntireTableWidgetPrivate
{
public:
    HSpecPelsWave *data;
};

HE_END_NAMESPACE
