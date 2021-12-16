#pragma once

#include "HImageCalendar.h"
#include <QMap>

HE_BEGIN_NAMESPACE

class HLunarCalendarInfo;

class HImageCalendarPrivate
{
public:
    HLunarCalendarInfo *lunar;
    HImageCalendar::CalendarStyle calendarStyle;
    QMap<HImageCalendar::CalendarStyle, QString> images;
};

HE_END_NAMESPACE
