#ifndef HLUNARCALENDARITEM_P_H
#define HLUNARCALENDARITEM_P_H

#include "HLunarCalendarItem.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLunarCalendarItemPrivate
{
public:
    HLunarCalendarItemPrivate();

public:
    bool select = false;                                // 是否选中
    bool showLunar = true;                              // 显示农历
    QString backgroundImage;                            // 背景图片
    HLunarCalendarItem::SelectType selectType;          // 选中模式
    QDate date;                                         // 当前日期
    QString lunar;                                      // 农历信息
    HLunarCalendarItem::DayType dayType;                // 当前日类型
    QColor borderColor = QColor(180, 180, 180);         // 边框颜色
    QColor weekColor = QColor(255, 0, 0);               // 周末颜色
    QColor superColor = QColor(255, 129, 6);            // 角标颜色
    QColor lunarColor = QColor(55, 156, 238);           // 农历节日颜色
    QColor currentTextColor = QColor(0, 0, 0);          // 当前月文字颜色
    QColor otherTextColor = QColor(200, 200, 200);      // 其他月文字颜色
    QColor selectTextColor = QColor(255, 255, 255);     // 选中日期文字颜色
    QColor hoverTextColor = QColor(250, 250, 250);      // 悬停日期文字颜色
    QColor currentLunarColor = QColor(150, 150, 150);   // 当前月农历文字颜色
    QColor otherLunarColor = QColor(200, 200, 200);     // 其他月农历文字颜色
    QColor selectLunarColor = QColor(255, 255, 255);    // 选中日期农历文字颜色
    QColor hoverLunarColor = QColor(250, 250, 250);     // 悬停日期农历文字颜色
    QColor currentBackground = QColor(255, 255, 255);   // 当前月背景颜色
    QColor otherBackground = QColor(240, 240, 240);     // 其他月背景颜色
    QColor selectBackground = QColor(208, 47, 18);      // 选中日期背景颜色
    QColor hoverBackground = QColor(204, 183, 180);     // 悬停日期背景颜色
    QStringList dayNames;                               // 农历日期
    bool hover = false;                                 // 鼠标是否悬停
    bool pressed = false;                               // 鼠标是否按下
};

HE_CONTROL_END_NAMESPACE

#endif // HLUNARCALENDARITEM_P_H
