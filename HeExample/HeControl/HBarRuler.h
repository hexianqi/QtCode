/***************************************************************************************************
**      2016-10-28  HBarRuler 柱状标尺控件。
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1：可设置精确度(小数点后几位)和间距
**                  2：可设置背景色/柱状颜色/线条颜色
**                  3：可设置长线条步长及短线条步长
**                  4：可启用动画及设置动画步长
**                  5：可设置范围值
**                  6：支持负数刻度值
***************************************************************************************************/

#pragma once

#include "HAbstractProgress.h"

HE_BEGIN_NAMESPACE

class HBarRulerPrivate;

class HBarRuler : public HAbstractProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBarRuler)
    Q_PROPERTY(int longStep READ longStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ shortStep WRITE setShortStep)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(bool animation READ isAnimation WRITE setAnimation)
    Q_PROPERTY(double animationStep READ animationStep WRITE setAnimationStep)
    Q_PROPERTY(QColor backgroundStart READ backgroundStart WRITE setBackgroundStart)
    Q_PROPERTY(QColor backgroundEnd READ backgroundEnd WRITE setBackgroundEnd)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor barBackground READ barBackground WRITE setBarBackground)
    Q_PROPERTY(QColor barColor READ barColor WRITE setBarColor)

public:
    explicit HBarRuler(QWidget *parent = nullptr);
    ~HBarRuler() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int longStep() const;
    int shortStep() const;
    int space() const;
    bool isAnimation() const;
    double animationStep() const;
    QColor backgroundStart() const;
    QColor backgroundEnd() const;
    QColor lineColor() const;
    QColor barBackground() const;
    QColor barColor() const;

public:
    void setValue(double value) override;
    void setDecimal(int value) override;
    void setLongStep(int value);
    void setShortStep(int value);
    void setSpace(int value);
    void setAnimation(bool b);
    void setAnimationStep(double value);
    void setBackgroundStart(const QColor &value);
    void setBackgroundEnd(const QColor &value);
    void setLineColor(const QColor &value);
    void setBarBackground(const QColor &value);
    void setBarColor(const QColor &value);

protected:
    HBarRuler(HBarRulerPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawRuler(QPainter *);
    void drawBar(QPainter *);

private:
    void init();
    void updateValue();
};

HE_END_NAMESPACE
