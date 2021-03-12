/***************************************************************************************************
**      2016-10-23  HClockGauge 时钟仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86185-ds-1.html#tpc
**                  1:可设置边框颜色
**                  2:可设置前景色背景色
**                  3:可设置时钟分钟秒钟指针颜色
**                  4:可设置刷新间隔
**                  5:鼠标右键可设置四种效果（普通效果/弹簧效果/连续效果/隐藏效果）
**                  6:增加设置系统时间公共槽函数,支持任意操作系统
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HClockGaugePrivate;

class HClockGauge : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor crownColorStart READ crownColorStart WRITE setCrownColorStart)
    Q_PROPERTY(QColor crownColorEnd READ crownColorEnd WRITE setCrownColorEnd)
    Q_PROPERTY(QColor pointerHourColor READ pointerHourColor WRITE setPointerHourColor)
    Q_PROPERTY(QColor pointerMinColor READ pointerMinColor WRITE setPointerMinColor)
    Q_PROPERTY(QColor pointerSecColor READ pointerSecColor WRITE setPointerSecColor)
    Q_PROPERTY(SecondStyle secondStyle READ secondStyle WRITE setSecondStyle)

public:
    enum SecondStyle
    {
        SecondStyle_Normal = 0,     // 普通效果
        SecondStyle_Spring = 1,     // 弹簧效果
        SecondStyle_Continue = 2,   // 连续效果
        SecondStyle_Hide = 3        // 隐藏效果
    };
    Q_ENUM(SecondStyle)

public:
    explicit HClockGauge(QWidget *parent = nullptr);
    ~HClockGauge() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor foreground() const;
    QColor background() const;
    QColor crownColorStart() const;
    QColor crownColorEnd() const;
    QColor pointerHourColor() const;
    QColor pointerMinColor() const;
    QColor pointerSecColor() const;
    SecondStyle secondStyle() const;

public slots:
    void setForeground(const QColor &value);
    void setBackground(const QColor &value);
    void setCrownColorStart(const QColor &value);
    void setCrownColorEnd(const QColor &value);
    void setPointerHourColor(const QColor &value);
    void setPointerMinColor(const QColor &value);
    void setPointerSecColor(const QColor &value);
    void setSecondStyle(SecondStyle value);

protected:
    HClockGauge(HClockGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawCrown(QPainter *);
    void drawBackground(QPainter *);
    void drawScale(QPainter *);
    void drawScaleLabel(QPainter *);
    void drawHour(QPainter *);
    void drawMin(QPainter *);
    void drawSec(QPainter *);
    void drawDot(QPainter *);

protected:
    QScopedPointer<HClockGaugePrivate> d_ptr;

private:
    void init();
    void updateTime();
    void updateSpring(const QVariant &);
};

HE_CONTROL_END_NAMESPACE
