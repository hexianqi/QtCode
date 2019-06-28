#ifndef HLUNARCALENDARINFO_P_H
#define HLUNARCALENDARINFO_P_H

#include "HLunarCalendarInfo.h"
#include <QtCore/QMap>

HE_CONTROL_BEGIN_NAMESPACE

class HLunarCalendarInfoPrivate
{
public:
    QList<int> monthAdd;                // 公历每月前面的天数
    QMap<int, QString> holiday;         // 公历节日
    QMap<int, QString> lunarFestival;   // 农历节日
    QStringList solarTerm;              // 二十四节气
    QStringList tiangan;                // 天干
    QStringList dizhi;                  // 地支
    QStringList animal;                 // 属相
    QStringList dayName;                // 农历日期名称
    QStringList monName;                // 农历月份名称
    QList<int> springFestival;          // 每年春节对应的公历日期
    QList<int> lunarData;
    QList<int> chineseTwentyFourData;
};

HE_CONTROL_END_NAMESPACE

#endif // HLUNARCALENDARINFO_P_H
