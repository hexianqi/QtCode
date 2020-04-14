/***************************************************************************************************
**      2016-11-20  HCarGauge 汽车仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85562-ds-1.html#tpc
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度
**                  3:可设置大刻度数量/小刻度数量
**                  4:可设置开始旋转角度/结束旋转角度
**                  5:可设置是否启用动画效果
**                  6:可设置外圆背景/内圆背景/饼圆三种颜色/刻度尺颜色/文字颜色
**                  7:自适应窗体拉伸,刻度尺和文字自动缩放
**                  8:可自由拓展各种渐变色,各圆的半径
**                  9:三色圆环按照比例设置范围角度 用户可以自由设置三色占用比例
**                  10:圆环样式可选择 三色圆环 当前圆环
**                  11:指示器样式可选择 圆形指示器 指针指示器 圆角指针指示器 三角形指示器
***************************************************************************************************/

#ifndef HCARGAUGE_H
#define HCARGAUGE_H

#include "HControlType.h"
#include "HCircleGauge.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCarGaugePrivate;

class HCarGauge : public HCircleGauge
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCarGauge)
    Q_PROPERTY(QColor outerCircleColor READ outerCircleColor WRITE setOuterCircleColor)
    Q_PROPERTY(QColor innerCircleColor READ innerCircleColor WRITE setInnerCircleColor)
    Q_PROPERTY(QColor coverCircleColor READ coverCircleColor WRITE setCoverCircleColor)
    Q_PROPERTY(QColor centerCircleColor READ centerCircleColor WRITE setCenterCircleColor)
    Q_PROPERTY(QColor pieColorStart READ pieColorStart WRITE setPieColorStart)
    Q_PROPERTY(QColor pieColorMid READ pieColorMid WRITE setPieColorMid)
    Q_PROPERTY(QColor pieColorEnd READ pieColorEnd WRITE setPieColorEnd)
    Q_PROPERTY(bool showOverlay READ isShowOverlay WRITE setShowOverlay)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)
    Q_PROPERTY(PieStyle pieStyle READ pieStyle WRITE setPieStyle)
    Q_PROPERTY(HControlType::PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PieStyle
    {
        PieStyle_Three = 0,             // 三色圆环
        PieStyle_Current = 1            // 当前圆环
    };
    Q_ENUM(PieStyle)

public:
    explicit HCarGauge(QWidget *parent = nullptr);

public:
    QColor outerCircleColor() const;
    QColor innerCircleColor() const;
    QColor coverCircleColor() const;
    QColor centerCircleColor() const;
    QColor pieColorStart() const;
    QColor pieColorMid() const;
    QColor pieColorEnd() const;
    bool isShowOverlay() const;
    QColor overlayColor() const;
    PieStyle pieStyle() const;
    HControlType::PointerStyle pointerStyle() const;

public slots:
    void setOuterCircleColor(const QColor &value);
    void setInnerCircleColor(const QColor &value);
    void setCoverCircleColor(const QColor &value);
    void setCenterCircleColor(const QColor &value);
    void setPieColorStart(const QColor &value);
    void setPieColorMid(const QColor &value);
    void setPieColorEnd(const QColor &value);
    void setShowOverlay(bool b);
    void setOverlayColor(const QColor &value);
    void setPieStyle(PieStyle value);
    void setPointerStyle(HControlType::PointerStyle value);

protected:
    HCarGauge(HCarGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawProgress(QPainter *, int radius) override;
    void drawPointer(QPainter *, int radius) override;
    void drawValue(QPainter *, int radius) override;
    void drawOuterCircle(QPainter *);
    void drawInnerCircle(QPainter *);
    void drawColorPie(QPainter *);
    void drawCoverCircle(QPainter *);
    void drawPointerCircle(QPainter *);
    void drawPointerIndicator(QPainter *);
    void drawPointerIndicatorR(QPainter *);
    void drawPointerTriangle(QPainter *);
    void drawPointerCenter(QPainter *);
    void drawCenterCircle(QPainter *);
};

HE_CONTROL_END_NAMESPACE

#endif // HCARGAUGE_H
