/***************************************************************************************************
**      2016-11-04  HThermometerRuler 柱状温度计控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85578-ds-1.html#tpc
**                  1:可设置精确度(小数点后几位)和间距
**                  2:可设置背景色/柱状颜色/线条颜色
**                  3:可设置长线条步长及短线条步长
**                  4:可启用动画及动画时间
**                  5:可设置范围值
**                  6:支持负数刻度值
**                  7:支持任意窗体大小缩放
**                  8:可设置柱状条位置(左侧,居中,右侧)
**                  9:可设置刻度尺位置(无,左侧,右侧,两侧)
**                  10:可设置用户设定目标值
***************************************************************************************************/

#pragma once

#include "HAnimationProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HThermometerRulerPrivate;

class HThermometerRuler : public HAnimationProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThermometerRuler)
    Q_PROPERTY(int longStep READ longStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ shortStep WRITE setShortStep)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(bool showUserValue READ isShowUserValue WRITE setShowUserValue)
    Q_PROPERTY(double userValue READ userValue WRITE setUserValue)
    Q_PROPERTY(QColor userValueColor READ userValueColor WRITE setUserValueColor)
    Q_PROPERTY(QColor backgroundStart READ backgroundStart WRITE setBackgroundStart)
    Q_PROPERTY(QColor backgroundEnd READ backgroundEnd WRITE setBackgroundEnd)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor barBackground READ barBackground WRITE setBarBackground)
    Q_PROPERTY(QColor barColor READ barColor WRITE setBarColor)
    Q_PROPERTY(BarPosition barPosition READ barPosition WRITE setBarPosition)
    Q_PROPERTY(TickPosition tickPosition READ tickPosition WRITE setTickPosition)

public:
    enum BarPosition
    {
        BarPosition_Left = 0,       //左侧显示
        BarPosition_Right = 1,      //右侧显示
        BarPosition_Center = 2      //居中显示
    };
    Q_ENUM(BarPosition)

    enum TickPosition
    {
        TickPosition_Null = 0,      //不显示
        TickPosition_Left = 1,      //左侧显示
        TickPosition_Right = 2,     //右侧显示
        TickPosition_Both = 3       //两侧显示
    };
    Q_ENUM(TickPosition)

public:
    explicit HThermometerRuler(QWidget *parent = nullptr);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int longStep() const;
    int shortStep() const;
    int space() const;
    bool isShowUserValue() const;
    double userValue() const;
    QColor userValueColor() const;
    QColor backgroundStart() const;
    QColor backgroundEnd() const;
    QColor lineColor() const;
    QColor barBackground() const;
    QColor barColor() const;
    BarPosition barPosition() const;
    TickPosition tickPosition() const;

public slots:
    void setLongStep(int value);
    void setShortStep(int value);
    void setSpace(int value);
    void setShowUserValue(bool b);
    void setUserValue(double value);
    void setUserValueColor(const QColor &);
    void setBackgroundStart(const QColor &);
    void setBackgroundEnd(const QColor &);
    void setLineColor(const QColor &);
    void setBarBackground(const QColor &);
    void setBarColor(const QColor &);
    void setBarPosition(BarPosition value);
    void setTickPosition(TickPosition value);

protected:
    HThermometerRuler(HThermometerRulerPrivate &p, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawBarBackground(QPainter *);
    void drawRuler(QPainter *, int type);
    void drawBar(QPainter *);
    void drawValue(QPainter *);
};

HE_CONTROL_END_NAMESPACE
