#ifndef HIMAGECALENDAR_P_H
#define HIMAGECALENDAR_P_H

#include "HImageCalendar.h"
#include <QMap>

HE_CONTROL_BEGIN_NAMESPACE

class HLunarCalendarInfo;

class HImageCalendarPrivate
{
public:
    HLunarCalendarInfo *lunar;
    HImageCalendar::CalendarStyle calendarStyle;
    QMap<HImageCalendar::CalendarStyle, QString> images;
};

HE_CONTROL_END_NAMESPACE

#endif // HIMAGECALENDAR_P_H
