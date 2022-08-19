#pragma once

#include "HLunarCalendarInfo.h"
#include <QtCore/QMap>

HE_BEGIN_NAMESPACE

class HLunarCalendarInfoPrivate
{
public:
    QList<int> monthDay;                // 公历每月有几天
    QList<int> monthAdd;                // 公历每月前面的天数
    QMap<int, QString> holiday;         // 公历节日
    QMap<int, QString> lunarFestival;   // 农历节日
    QStringList solarTerm;              // 二十四节气
    QStringList tiangan;                // 天干
    QStringList dizhi;                  // 地支
    QStringList animal;                 // 属相
    QStringList dayName;                // 农历日期名称
    QStringList monthName;              // 农历月份名称
    QList<int> springFestival;          // 春节公历日期
    QList<int> lunarData;               // 农历每月数据
    QList<int> chineseTwentyFourData;   // 农历二十四节气数据
};

HE_END_NAMESPACE
