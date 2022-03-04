#pragma once

#include "HSpecPelsWaveWidget.h"

class QSpinBox;
class HEntireTableWidget;

HE_BEGIN_NAMESPACE

class HSpecPelsWaveWidgetPrivate
{
public:
    QSpinBox *spinBox = nullptr;
    HEntireTableWidget *tableWidget = nullptr;
    HSpecPelsWave *data;
};

HE_END_NAMESPACE
