/***************************************************************************************************
**      2019-06-28  HImageCalendar 图片背景日历控件
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1:可设置六种图片背景(黄色/蓝色/褐色/灰色/紫色/红色)风格
**                  2:显示当前日期及农历
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HImageCalendarPrivate;

class HImageCalendar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(CalendarStyle calendarStyle  READ calendarStyle  WRITE setCalendarStyle)

public:
    enum CalendarStyle
    {
        CalendarStyle_Yellow = 0,   //黄色风格
        CalendarStyle_Blue = 1,     //蓝色风格
        CalendarStyle_Brown = 2,    //褐色风格
        CalendarStyle_Gray = 3,     //灰色风格
        CalendarStyle_Purple = 4,   //紫色风格
        CalendarStyle_Red = 5       //红色风格
    };
    Q_ENUM(CalendarStyle)

public:
    explicit HImageCalendar(QWidget *parent = nullptr);
    ~HImageCalendar() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    CalendarStyle calendarStyle()const;

public:
    void setCalendarStyle(CalendarStyle value);

protected:
    HImageCalendar(HImageCalendarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    QImage createImage();
    void changeStyle(QAction *);

protected:
    QScopedPointer<HImageCalendarPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
