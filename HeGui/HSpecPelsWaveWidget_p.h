#pragma once

#include "HSpecPelsWaveWidget.h"

class QCheckBox;
class QSpinBox;
class HEntireTableWidget;

HE_BEGIN_NAMESPACE

class HSpecPelsWaveWidgetPrivate
{
public:
    QCheckBox *checkBox = nullptr;
    QSpinBox *spinBox = nullptr;
    QSpinBox *spinBox2 = nullptr;
    HEntireTableWidget *tableWidget = nullptr;
    HSpecPelsWave *data;
};

HE_END_NAMESPACE
