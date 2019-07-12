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

#include "HControlType.h"
#include "HCircleGauge.h"

HE_CONTROL_BEGIN_NAMESPACE

class HArcGaugePrivate;

class HArcGauge : public HCircleGauge
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HArcGauge)
    Q_ENUMS(PointerStyle)
    Q_PROPERTY(QColor arcColor READ arcColor WRITE setArcColor)
    Q_PROPERTY(PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    explicit HArcGauge(QWidget *parent = nullptr);
    ~HArcGauge() override;

public:
    QColor arcColor() const;    
    PointerStyle pointerStyle() const;

public slots:    
    void setArcColor(const QColor &value);
    void setPointerStyle(PointerStyle value);

protected:
    HArcGauge(HArcGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawProgress(QPainter *, int radius) override;
    void drawPointer(QPainter *, int radius) override;
    void drawPointerCircle(QPainter *);
    void drawPointerIndicator(QPainter *);
    void drawPointerIndicatorR(QPainter *);
    void drawPointerTriangle(QPainter *);
    void drawPointerCenter(QPainter *);
};

HE_CONTROL_END_NAMESPACE

#endif // HARCGAUGE_H
