#include "HLunarCalendarInfo_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HLunarCalendarInfo::HLunarCalendarInfo(QObject *parent) :
    QObject(parent),
    d_ptr(new HLunarCalendarInfoPrivate)
{
    init();
}

HLunarCalendarInfo::HLunarCalendarInfo(HLunarCalendarInfoPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    init();
}

HLunarCalendarInfo::~HLunarCalendarInfo() = default;

bool HLunarCalendarInfo::isLoopYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int HLunarCalendarInfo::monthDays(int year, int month)
{
    if (month < 1 || month > 12)
        return 0;
    auto add = (isLoopYear(year) && month == 2) ? 1 : 0;
    return d_ptr->monthDay[month - 1] + add;
}

int HLunarCalendarInfo::totalMonthDays(int year, int month)
{
    if (month < 1 || month > 12)
        return 0;
    auto add = (isLoopYear(year) && month > 2) ? 1 : 0;
    return d_ptr->monthAdd[month - 1] + add;
}

int HLunarCalendarInfo::firstDayOfWeek(int year, int month)
{
    int week = 0;
    week = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    week += totalMonthDays(year, month);
    return week % 7;
}

QString HLunarCalendarInfo::holiday(int month, int day)
{
    int temp = (month << 8) | day;
    return d_ptr->holiday.value(temp);
}

QString HLunarCalendarInfo::lunarFestival(int month, int day)
{
    int temp = (month << 8) | day;
    return d_ptr->lunarFestival.value(temp);
}

QString HLunarCalendarInfo::solarTerms(int year, int month, int day)
{
    int index = (year - 1970) * 12 + month - 1;
    if (day < 15 && (d_ptr->chineseTwentyFourData.at(index) >> 4) == 15 - day)
        return d_ptr->solarTerm.at(2 * (month - 1));
    if (day > 15 && (d_ptr->chineseTwentyFourData.at(index) & 0x0F) == day - 15)
        return d_ptr->solarTerm.at(2 * (month - 1) + 1);
    return QString();
}

QString HLunarCalendarInfo::lunarYear(int year)
{
    int t = year - 4;
    return QString("%1%2%3").arg(d_ptr->tiangan.at(t % 10), d_ptr->dizhi.at(t % 12), d_ptr->animal.at(t % 12));
}

QString HLunarCalendarInfo::lunarYearMonthDay(int year, int month, int day)
{
    return lunarInfo(year, month, day, true, true, true);
}

QString HLunarCalendarInfo::lunarMonthDay(int year, int month, int day)
{
    return lunarInfo(year, month, day, false, true, true);
}

QString HLunarCalendarInfo::lunarDay(int year, int month, int day)
{
    return lunarInfo(year, month, day, false, false, true);
}

QString HLunarCalendarInfo::lunarInfo(int year, int month, int day, bool yearInfo, bool monthInfo, bool dayInfo)
{
    QString holiday, solarTerms, lunarFestival, lunarYear, lunarMonth, lunarDay;
    lunarInfo(year, month, day, holiday, solarTerms, lunarFestival, lunarYear, lunarMonth, lunarDay);

    // 农历节日优先,其次农历节气,然后公历节日,最后才是农历月份名称
    if (!lunarFestival.isEmpty())
        lunarDay = lunarFestival;
    else if (!solarTerms.isEmpty())
        lunarDay = solarTerms;
    else if (!holiday.isEmpty())
        lunarDay = holiday;

    return QString("%1%2%3").arg(yearInfo ? lunarYear + "年" : "", monthInfo ? lunarMonth : "", dayInfo ? lunarDay : "");
}

void HLunarCalendarInfo::lunarInfo(int year, int month, int day, QString &holiday, QString &solarTerms, QString &lunarFestival, QString &lunarYear, QString &lunarMonth, QString &lunarDay)
{
    if (year < 1901 || year > 2099 || month < 1 || month > 12 || day < 1 || day > 31)
        return;

    int info, end, monTemp, k, n, bit;

    holiday = this->holiday(month, day);
    solarTerms = this->solarTerms(year, month, day);

    // 现在计算农历:获得当年春节的公历日期(比如：2015年春节日期为(2月19日))
    // 以此为分界点,2.19前面的农历是2014年农历(用2014年农历数据来计算)
    // 2.19以及之后的日期，农历为2015年农历(用2015年农历数据来计算)
    monTemp = year - 1968;
    int springMonth = d_ptr->springFestival.at(monTemp) / 100;
    int springDaty = d_ptr->springFestival.at(monTemp) % 100;

    if (month < springMonth)
    {
        monTemp--;
        info = 365 + day + d_ptr->monthAdd.at(month - 1) - 31 * ((d_ptr->springFestival.at(monTemp) / 100) - 1) - d_ptr->springFestival.at(monTemp) % 100 + 1;
        if (year % 4 == 0 && month > 2)
            info = info + 1;
        if ((year - 1) % 4 == 0)
            info = info + 1;
    }
    else if (month == springMonth)
    {
        if (day < springDaty)
        {
            monTemp--;
            info = 365 + day + d_ptr->monthAdd.at(month - 1) - 31 * ((d_ptr->springFestival.at(monTemp) / 100) - 1) - d_ptr->springFestival.at(monTemp) % 100 + 1;
            if (year % 4 == 0 && month > 2)
                info = info + 1;
            if ((year - 1) % 4 == 0)
                info = info + 1;
        }
        else
        {
            info = day + d_ptr->monthAdd.at(month - 1) - 31 * ((d_ptr->springFestival.at(monTemp) / 100) - 1) - d_ptr->springFestival.at(monTemp) % 100 + 1;
            if (year % 4 == 0 && month > 2)
                info = info + 1;
        }
    }
    else
    {
        info = day + d_ptr->monthAdd.at(month - 1) - 31 * ((d_ptr->springFestival.at(monTemp) / 100) - 1) - d_ptr->springFestival.at(monTemp) % 100 + 1;
        if (year % 4 == 0 && month > 2)
            info = info + 1;
    }

    // 计算农历天干地支月日
    end = 0;
    k = 11;
    n = 11;
    while (end != 1)
    {
        k = d_ptr->lunarData.at(monTemp) < 4095 ? 11 : 12;
        n = k;
        while (n >= 0)
        {
            bit = d_ptr->lunarData.at(monTemp);
            bit = bit >> n;
            bit = bit % 2;
            if (info <= (29 + bit))
            {
                end = 1;
                break;
            }
            info = info - 29 - bit;
            n = n - 1;
        }
        if (end)
            break;
        monTemp = monTemp + 1;
    }

    // 农历的年月日
    year = 1969 + monTemp - 1;
    month = k - n + 1;
    day = info;

    if (k == 12)
    {
        if (month == (d_ptr->lunarData.at(monTemp) / 65536) + 1)
            month = 1 - month;
        else if (month > (d_ptr->lunarData.at(monTemp) / 65536) + 1)
            month = month - 1;
    }

    lunarYear = this->lunarYear(year);
    lunarMonth = d_ptr->monthName.at(qAbs(month));
    lunarDay = d_ptr->dayName.at(qAbs(day));
    lunarFestival = this->lunarFestival(qAbs(month), qAbs(day));
}

void HLunarCalendarInfo::init()
{
    d_ptr->monthDay << 31 << 28 << 31 << 30 << 31 << 30 << 31 << 31 << 30 << 31 << 30 << 31;
    d_ptr->monthAdd << 0 << 31 << 59 << 90 << 120 << 151 << 181 << 212 << 243 << 273 << 304 << 334;
    d_ptr->holiday.insert(0x0101, tr("元旦"));
    d_ptr->holiday.insert(0x020E, tr("情人节"));
    d_ptr->holiday.insert(0x0308, tr("妇女节"));
    d_ptr->holiday.insert(0x030C, tr("植树节"));
    d_ptr->holiday.insert(0x0401, tr("愚人节"));
    d_ptr->holiday.insert(0x0501, tr("劳动节"));
    d_ptr->holiday.insert(0x0504, tr("青年节"));
    d_ptr->holiday.insert(0x0601, tr("儿童节"));
    d_ptr->holiday.insert(0x0701, tr("建党节"));
    d_ptr->holiday.insert(0x0801, tr("建军节"));
    d_ptr->holiday.insert(0x090A, tr("教师节"));
    d_ptr->holiday.insert(0x0A01, tr("国庆节"));
    d_ptr->holiday.insert(0x0C18, tr("平安夜"));
    d_ptr->holiday.insert(0x0C19, tr("圣诞节"));
    d_ptr->lunarFestival.insert(0x0101, tr("春节"));
    d_ptr->lunarFestival.insert(0x010F, tr("元宵节"));
    d_ptr->lunarFestival.insert(0x0202, tr("龙抬头"));
    d_ptr->lunarFestival.insert(0x0505, tr("端午节"));
    d_ptr->lunarFestival.insert(0x0707, tr("七夕节"));
    d_ptr->lunarFestival.insert(0x080F, tr("中秋节"));
    d_ptr->lunarFestival.insert(0x0909, tr("重阳节"));
    d_ptr->lunarFestival.insert(0x0C08, tr("腊八节"));

    d_ptr->solarTerm << tr("小寒") << tr("大寒") << tr("立春") << tr("雨水") << tr("惊蛰") << tr("春分") << tr("清明") << tr("谷雨")
                     << tr("立夏") << tr("小满") << tr("芒种") << tr("夏至") << tr("小暑") << tr("大暑") << tr("立秋") << tr("处暑")
                     << tr("白露") << tr("秋分") << tr("寒露") << tr("霜降") << tr("立冬") << tr("小雪") << tr("大雪") << tr("冬至");
    d_ptr->tiangan << tr("甲") << tr("乙") << tr("丙") << tr("丁") << tr("戊") << tr("己") << tr("庚") << tr("辛") << tr("壬") << tr("癸");
    d_ptr->dizhi   << tr("子") << tr("丑") << tr("寅") << tr("卯") << tr("辰") << tr("巳") << tr("午") << tr("未") << tr("申") << tr("酉") << tr("戌") << tr("亥");
    d_ptr->animal  << tr("鼠") << tr("牛") << tr("虎") << tr("兔") << tr("龙") << tr("蛇") << tr("马") << tr("羊") << tr("猴") << tr("鸡") << tr("狗") << tr("猪");


    d_ptr->dayName << tr("*") << tr("初一") << tr("初二") << tr("初三") << tr("初四") << tr("初五") << tr("初六") << tr("初七")
                   << tr("初八") << tr("初九") << tr("初十") << tr("十一") << tr("十二") << tr("十三") << tr("十四") << tr("十五")
                   << tr("十六") << tr("十七") << tr("十八") << tr("十九") << tr("二十") << tr("廿一") << tr("廿二") << tr("廿三")
                   << tr("廿四") << tr("廿五") << tr("廿六") << tr("廿七") << tr("廿八") << tr("廿九") << tr("三十");

    d_ptr->monthName << tr("*") << tr("正月") << tr("二月") << tr("三月") << tr("四月") << tr("五月") << tr("六月")
                     << tr("七月") << tr("八月") << tr("九月") << tr("十月") << tr("冬月") << tr("腊月");

    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1970
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0x96 << 0xA6 << 0x97 << 0x97 << 0x78 << 0x79 << 0x79 << 0x69 << 0x78 << 0x77; // 1971
    d_ptr->chineseTwentyFourData << 0x96 << 0xA4 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1972
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB5 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 1973
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1974
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0x96 << 0xA6 << 0x97 << 0x97 << 0x78 << 0x79 << 0x78 << 0x69 << 0x78 << 0x77; // 1975
    d_ptr->chineseTwentyFourData << 0x96 << 0xA4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x89 << 0x88 << 0x78 << 0x87 << 0x87; // 1976
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 1977
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x78 << 0x87; // 1978
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0x96 << 0xA6 << 0x96 << 0x97 << 0x78 << 0x79 << 0x78 << 0x69 << 0x78 << 0x77; // 1979
    d_ptr->chineseTwentyFourData << 0x96 << 0xA4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1980
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x77 << 0x87; // 1981
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 1982
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x78 << 0x79 << 0x78 << 0x69 << 0x78 << 0x77; // 1983
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1984
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0xA6 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 1985
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 1986
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x79 << 0x78 << 0x69 << 0x78 << 0x87; // 1987
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 1988
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0xA5 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1989
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 1990
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x86 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1991
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 1992
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1993
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 1994
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x76 << 0x78 << 0x69 << 0x78 << 0x87; // 1995
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 1996
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 1997
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 1998
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 1999
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2000
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2001
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 2002
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 2003
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2004
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2005
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2006
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x69 << 0x78 << 0x87; // 2007
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x87 << 0x78 << 0x87 << 0x86; // 2008
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2009
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2010
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x78 << 0x87; // 2011
    d_ptr->chineseTwentyFourData << 0x96 << 0xB4 << 0xA5 << 0xB5 << 0xA5 << 0xA6 << 0x87 << 0x88 << 0x87 << 0x78 << 0x87 << 0x86; // 2012
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2013
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2014
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x97 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 2015
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x87 << 0x88 << 0x87 << 0x78 << 0x87 << 0x86; // 2016
    d_ptr->chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2017
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0xA6 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2018
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 2019
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x86; // 2020
    d_ptr->chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2021
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0xA5 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2022
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x79 << 0x77 << 0x87; // 2023
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2024
    d_ptr->chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2025
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2026
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 2027
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2028
    d_ptr->chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2029
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2030
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0x96 << 0x96 << 0x88 << 0x78 << 0x78 << 0x78 << 0x87 << 0x87; // 2031
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2032
    d_ptr->chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2033
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x78 << 0x88 << 0x78 << 0x87 << 0x87; // 2034
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB4 << 0x96 << 0xA5 << 0xA6 << 0x96 << 0x88 << 0x88 << 0x78 << 0x78 << 0x87 << 0x87; // 2035
    d_ptr->chineseTwentyFourData << 0x95 << 0xB4 << 0xA5 << 0xB4 << 0xA5 << 0xA6 << 0x97 << 0x87 << 0x87 << 0x78 << 0x87 << 0x96; // 2036
    d_ptr->chineseTwentyFourData << 0xA5 << 0xC3 << 0xA5 << 0xB5 << 0xA6 << 0xA6 << 0x87 << 0x88 << 0x88 << 0x78 << 0x87 << 0x86; // 2037
    d_ptr->chineseTwentyFourData << 0xA5 << 0xB3 << 0xA5 << 0xA5 << 0xA6 << 0xA6 << 0x88 << 0x88 << 0x88 << 0x78 << 0x87 << 0x87; // 2038

    d_ptr->springFestival << 130 << 217 << 206;                                                    // 1968--1970
    d_ptr->springFestival << 127 << 215 << 203 << 123 << 211 << 131 << 218 << 207 << 128 << 216;   // 1971--1980
    d_ptr->springFestival << 205 << 125 << 213 << 202 << 220 << 209 << 219 << 217 << 206 << 127;   // 1981--1990
    d_ptr->springFestival << 215 << 204 << 123 << 210 << 131 << 219 << 207 << 128 << 216 << 205;   // 1991--2000
    d_ptr->springFestival << 124 << 212 << 201 << 122 << 209 << 129 << 218 << 207 << 126 << 214;   // 2001--2010
    d_ptr->springFestival << 203 << 123 << 210 << 131 << 219 << 208 << 128 << 216 << 205 << 125;   // 2011--2020
    d_ptr->springFestival << 212 << 201 << 122 << 210 << 129 << 217 << 206 << 126 << 213 << 203;   // 2021--2030
    d_ptr->springFestival << 123 << 211 << 131 << 219 << 208 << 128 << 215 << 204 << 124 << 212;   // 2031--2040

    // 16--18位表示闰几月 0--12位表示农历每月的数据 高位表示1月 低位表示12月(农历闰月就会多一个月)
    d_ptr->lunarData << 461653 << 1386 << 2413;                                                               // 1968--1970
    d_ptr->lunarData << 330077 << 1197 << 2637 << 268877 << 3365 << 531109 << 2900 << 2922 << 398042 << 2395; // 1971--1980
    d_ptr->lunarData << 1179 << 267415 << 2635 << 661067 << 1701 << 1748 << 398772 << 2742 << 2391 << 330031; // 1981--1990
    d_ptr->lunarData << 1175 << 1611 << 200010 << 3749 << 527717 << 1452 << 2742 << 332397 << 2350 << 3222;   // 1991--2000
    d_ptr->lunarData << 268949 << 3402 << 3493 << 133973 << 1386 << 464219 << 605 << 2349 << 334123 << 2709;  // 2001--2010
    d_ptr->lunarData << 2890 << 267946 << 2773 << 592565 << 1210 << 2651 << 395863 << 1323 << 2707 << 265877; // 2011--2020
    d_ptr->lunarData << 1706 << 2773 << 133557 << 1206 << 398510 << 2638 << 3366 << 335142 << 3411 << 1450;   // 2021--2030
    d_ptr->lunarData << 200042 << 2413 << 723293 << 1197 << 2637 << 399947 << 3365 << 3410 << 334676 << 2906; // 2031--2040
}

HE_CONTROL_END_NAMESPACE
