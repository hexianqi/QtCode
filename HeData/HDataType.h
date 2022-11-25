#pragma once

#include "HNamespace.h"
#include <QtCore/QMetaType>

HE_BEGIN_NAMESPACE

enum HSpecType
{
    Setting,
    Fitting,
    StdCurve,
    PelsWave,
    Luminous
};

enum HElecType
{
    OutputVoltage,
    OutputCurrent,
    MeasuredVoltage,
    MeasuredCurrent,
    ReverseVoltage,
    ReverseCurrent
};

enum HQualityType
{
    Damage,
    Criterion
};

enum HQualityReport
{
    InvalidQuality,
    InvalidData,
    Broken,
    NoPass,
    Passing,
    Spacer
};

HE_END_NAMESPACE

#ifdef HE_NAMESPACE
    Q_DECLARE_METATYPE(HE_NAMESPACE::HQualityReport);
#else
    Q_DECLARE_METATYPE(HQualityReport);
#endif


