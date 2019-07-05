/***************************************************************************************************
**      2019-06-27  HArcGauge 圆弧仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85801.html
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度,最大支持小数点后3位
**                  3:可设置大刻度数量/小刻度数量
**                  4:可设置开始旋转角度/结束旋转角度
**                  5:可设置是否启用动画效果以及动画效果每次移动的步长
**                  6:可设置外圆背景/内圆背景/饼圆三种颜色/刻度尺颜色/文字颜色
**                  7:自适应窗体拉伸,刻度尺和文字自动缩放
**                  8:可自由拓展各种渐变色,各圆的半径
**                  9:指示器样式可选择 圆形指示器 指针指示器 圆角指针指示器 三角形指示器
***************************************************************************************************/

#ifndef HARCGAUGE_H
#define HARCGAUGE_H

#include "HAnimationProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HArcGaugePrivate;

class HArcGauge : public HAnimationProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HArcGauge)
    Q_ENUMS(PointerStyle)
    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int angleStart READ angleStart WRITE setAngleStart)
    Q_PROPERTY(int angleEnd READ angleEnd WRITE setAngleEnd)
    Q_PROPERTY(QColor arcColor READ arcColor WRITE setArcColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor scaleLabelColor READ scaleLabelColor WRITE setScaleLabelColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)
    Q_PROPERTY(PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PointerStyle
    {
        Circle = 0,        // 圆形指示器
        Indicator = 1,     // 指针指示器
        IndicatorR = 2,    // 圆角指针指示器
        Triangle = 3       // 三角形指示器
    };

public:
    explicit HArcGauge(QWidget *parent = nullptr);
    ~HArcGauge() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int scaleMajor() const;
    int scaleMinor() const;
    int angleStart() const;
    int angleEnd() const;
    QColor arcColor() const;
    QColor scaleColor() const;
    QColor scaleLabelColor() const;
    QColor textColor() const;
    QColor pointerColor() const;
    PointerStyle pointerStyle() const;

public slots:
    void setScaleMajor(int value);
    void setScaleMinor(int value);
    void setAngleStart(int value);
    void setAngleEnd(int value);
    void setArcColor(const QColor &value);
    void setScaleColor(const QColor &value);
    void setScaleLabelColor(const QColor &value);
    void setTextColor(const QColor &value);
    void setPointerColor(const QColor &value);
    void setPointerStyle(PointerStyle value);

protected:
    HArcGauge(HArcGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawArc(QPainter *);
    void drawScale(QPainter *);
    void drawScaleLabel(QPainter *);
    void drawPointer(QPainter *);
    void drawPointerCircle(QPainter *);
    void drawPointerIndicator(QPainter *);
    void drawPointerIndicatorR(QPainter *);
    void drawPointerTriangle(QPainter *);
    void drawRoundCircle(QPainter *);
    void drawCenterCircle(QPainter *);
    void drawValue(QPainter *);

protected:
    double angleSpan();
    double toAngle(double value);
};

HE_CONTROL_END_NAMESPACE

#endif // HARCGAUGE_H
