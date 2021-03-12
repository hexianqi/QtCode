#pragma once

#include "HLunarCalendarWidget.h"

class QComboBox;
class QLabel;

HE_CONTROL_BEGIN_NAMESPACE

class HLunarCalendarInfo;

class HLunarCalendarWidgetPrivate
{
public:
    HLunarCalendarWidgetPrivate();

public:
    QDate date;                                             // 当前日期
    HLunarCalendarWidget::WeekNameFormat weekNameFormat;    // 星期名称格式
    QColor weekTextColor = QColor(255, 255, 255);           // 星期名称文字颜色
    QColor weekBackground = QColor(22, 160, 134);           // 星期名称背景色
    bool showLunar = true;
    QString backgroundImage;                                // 背景图片
    HLunarCalendarItem::SelectType selectType;              // 选中模式
    QColor borderColor = QColor(180, 180, 180);             // 边框颜色
    QColor weekColor = QColor(255, 0, 0);                   // 周末颜色
    QColor superColor = QColor(255, 129, 6);                // 角标颜色
    QColor lunarColor = QColor(55, 156, 238);               // 农历节日颜色
    QColor currentTextColor = QColor(0, 0, 0);              // 当前月文字颜色
    QColor otherTextColor = QColor(200, 200, 200);          // 其他月文字颜色
    QColor selectTextColor = QColor(255, 255, 255);         // 选中日期文字颜色
    QColor hoverTextColor = QColor(250, 250, 250);          // 悬停日期文字颜色
    QColor currentLunarColor = QColor(150, 150, 150);       // 当前月农历文字颜色
    QColor otherLunarColor = QColor(200, 200, 200);         // 其他月农历文字颜色
    QColor selectLunarColor = QColor(255, 255, 255);        // 选中日期农历文字颜色
    QColor hoverLunarColor = QColor(250, 250, 250);         // 悬停日期农历文字颜色
    QColor currentBackground = QColor(255, 255, 255);       // 当前月背景颜色
    QColor otherBackground = QColor(240, 240, 240);         // 其他月背景颜色
    QColor selectBackground = QColor(208, 47, 18);          // 选中日期背景颜色
    QColor hoverBackground = QColor(204, 183, 180);         // 悬停日期背景颜色

public:
    HLunarCalendarInfo *info;
    QFont iconFont;                                         // 图形字体
    bool comboBoxClicked = false;                           // 按钮单击，避开下拉选择重复触发
    QComboBox *comboBoxYear;                                // 年份下拉框
    QComboBox *comboBoxMonth;                               // 月份下拉框
    QList<QLabel *> labelWeeks;                             // 顶部星期名称
    QList<HLunarCalendarItem *> dayItems;                   // 日期元素
};

HE_CONTROL_END_NAMESPACE
