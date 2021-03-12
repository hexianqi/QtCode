/***************************************************************************************************
**      2019-06-28  HLunarCalendarInfo 农历信息类
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1:计算是否闰年
**                  2:计算国际节日
**                  3:计算二十四节气
**                  4:计算农历年 天干+地支+生肖
**                  5:计算指定年月日农历信息,包括公历节日和农历节日及二十四节气
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HLunarCalendarInfoPrivate;

class HLunarCalendarInfo : public QObject
{
    Q_OBJECT

public:
    explicit HLunarCalendarInfo(QObject *parent = nullptr);
    ~HLunarCalendarInfo() override;

public:
    // 是否闰年
    bool isLoopYear(int year);
    // 指定年月该月共多少天
    int monthDays(int year, int month);
    // 指定年月对应到该月有几天
    int totalMonthDays(int year, int month);
    // 指定年月对应星期
    int firstDayOfWeek(int year, int month);
    // 国际节日
    QString holiday(int month, int day);
    // 农历节日(必须传入农历年份月份)
    QString lunarFestival(int month, int day);
    // 二十四节气
    QString solarTerms(int year, int month, int day);
    // 农历年 天干+地支+生肖
    QString lunarYear(int year);
    // 指定年月日农历年份及属相
    QString lunarYearMonthDay(int year, int month, int day);
    QString lunarMonthDay(int year, int month, int day);
    QString lunarDay(int year, int month, int day);
    // 指定年月日农历信息
    QString lunarInfo(int year, int month, int day, bool yearInfo, bool monthInfo, bool dayInfo);
    // 指定年月日农历信息,包括公历节日和农历节日及二十四节气
    void lunarInfo(int year, int month, int day, QString &holiday, QString &solarTerms, QString &lunarFestival, QString &lunarYear, QString &lunarMonth, QString &lunarDay);

protected:
    HLunarCalendarInfo(HLunarCalendarInfoPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HLunarCalendarInfoPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
