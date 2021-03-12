#pragma once

#include "HDataGlobal.h"
#include <QtCore/QMetaType>

HE_DATA_BEGIN_NAMESPACE

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
    Passing
};

HE_DATA_END_NAMESPACE

Q_DECLARE_METATYPE(HeData::HQualityReport);
