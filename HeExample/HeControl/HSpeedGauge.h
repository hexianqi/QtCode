/***************************************************************************************************
**      2019-07-09  HSpeedGauge 速度仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85567-ds-1.html#tpc
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度,最大支持小数点后3位
**                  3:可设置大刻度数量/小刻度数量
**                  4:可设置开始旋转角度/结束旋转角度
**                  5:可设置是否启用动画效果
**                  6:可设置三色圆环占比例
**                  7:自适应窗体拉伸,刻度尺和文字自动缩放
***************************************************************************************************/

#ifndef HSPEEDGAUGE_H
#define HSPEEDGAUGE_H

#include "HAnimationProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HSpeedGaugePrivate;

class HSpeedGauge : public HAnimationProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpeedGauge)
    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int angleStart READ angleStart WRITE setAngleStart)
    Q_PROPERTY(int angleEnd READ angleEnd WRITE setAngleEnd)
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)
    Q_PROPERTY(int ringPercentStart READ ringPercentStart WRITE setRingPercentStart)
    Q_PROPERTY(int ringPercentMid READ ringPercentMid WRITE setRingPercentMid)
    Q_PROPERTY(int ringPercentEnd READ ringPercentEnd WRITE setRingPercentEnd)
    Q_PROPERTY(QColor ringColorStart READ ringColorStart WRITE setRingColorStart)
    Q_PROPERTY(QColor ringColorMid READ ringColorMid WRITE setRingColorMid)
    Q_PROPERTY(QColor ringColorEnd READ ringColorEnd WRITE setRingColorEnd)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

public:
    explicit HSpeedGauge(QWidget *parent = nullptr);
    ~HSpeedGauge() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int scaleMajor() const;
    int scaleMinor() const;
    int angleStart() const;
    int angleEnd() const;
    int ringWidth() const;
    int ringPercentStart() const;
    int ringPercentMid() const;
    int ringPercentEnd() const;
    QColor ringColorStart() const;
    QColor ringColorMid() const;
    QColor ringColorEnd() const;
    QColor pointerColor() const;
    QColor textColor() const;

public slots:
    void setDecimal(int value) override;
    void setScaleMajor(int value);
    void setScaleMinor(int value);
    void setAngleStart(int value);
    void setAngleEnd(int value);
    void setRingWidth(int value);
    void setRingPercentStart(int value);
    void setRingPercentMid(int value);
    void setRingPercentEnd(int value);
    void setRingColorStart(const QColor &value);
    void setRingColorMid(const QColor &value);
    void setRingColorEnd(const QColor &value);
    void setPointerColor(const QColor &value);
    void setTextColor(const QColor &value);

protected:
    HSpeedGauge(HSpeedGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawRing(QPainter *);
    void drawScale(QPainter *);
    void drawScaleLabel(QPainter *);
    void drawPointer(QPainter *);
    void drawValue(QPainter *);

private:
    void init();
    double angleSpan();
    double toAngle(double value);

};

HE_CONTROL_END_NAMESPACE

#endif // HSPEEDGAUGE_H

//    QLCDNumber *lcd;                //数码管
//    //设置动画显示的步长
//    void setAnimationStep(double animationStep);

//    //设置饼圆宽度
//    void setRingWidth(int ringWidth);

//    //设置三个圆环所占比例
//    void setRingStartPercent(int ringStartPercent);
//    void setRingMidPercent(int ringMidPercent);
//    void setRingEndPercent(int ringEndPercent);

//    //设置三个圆环颜色
//    void setRingColorStart(const QColor &ringColorStart);
//    void setRingColorMid(const QColor &ringColorMid);
//    void setRingColorEnd(const QColor &ringColorEnd);

//    //设置指针颜色
//    void setPointerColor(const QColor &pointerColor);
//    //设置文本颜色
//    void setTextColor(const QColor &textColor);

//Q_SIGNALS:
//    void valueChanged(int value);
//};

//#endif //GAUGESPEED_H
