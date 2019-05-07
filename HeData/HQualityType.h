/***************************************************************************************************
**      2019-05-05  HQualityType 品质报告。
***************************************************************************************************/

#ifndef HQUALITYTYPE_H
#define HQUALITYTYPE_H

#include "HDataGlobal.h"
#include <QtCore/QMetaType>

HE_DATA_BEGIN_NAMESPACE

enum HQualityReport
{
    InvalidQuality,
    InvalidData,
    Damage,
    NoPass,
    Passing
};

HE_DATA_END_NAMESPACE

Q_DECLARE_METATYPE(HeData::HQualityReport);

#endif // HQUALITYTYPE_H
