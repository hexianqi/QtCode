#pragma once

#include "HSpecPelsWaveWidget.h"
#include "HePlugin/HEntireTableWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecPelsWaveWidgetPrivate : public HEntireTableWidgetPrivate
{
public:
    HSpecPelsWave *data;
};

HE_GUI_END_NAMESPACE
