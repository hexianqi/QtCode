/***************************************************************************************************
**      2019-06-28  HImageCalendar 图片背景日历控件
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1:可设置六种图片背景(黄色/蓝色/褐色/灰色/紫色/红色)风格
**                  2:显示当前日期及农历
***************************************************************************************************/

#ifndef HIMAGECALENDAR_H
#define HIMAGECALENDAR_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HImageCalendarPrivate;

class HImageCalendar : public QWidget
{
    Q_OBJECT
    Q_ENUMS(CalendarStyle)
    Q_PROPERTY(CalendarStyle calendarStyle READ calendarStyle WRITE setCalendarStyle)

public:
    enum CalendarStyle
    {
        Yellow = 0,   //黄色风格
        Blue = 1,     //蓝色风格
        Brown = 2,    //褐色风格
        Gray = 3,     //灰色风格
        Purple = 4,   //紫色风格
        Red = 5       //红色风格
    };

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

HE_CONTROL_END_NAMESPACE

#endif // HIMAGECALENDAR_H
