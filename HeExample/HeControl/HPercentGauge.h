/***************************************************************************************************
**      2019-07-02  HPercentGauge 百分比仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85620-ds-1.html#tpc
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度,最大支持小数点后3位
**                  3:可设置大刻度数量/小刻度数量
**                  4:可设置开始旋转角度/结束旋转角度
**                  5:可设置仪表盘的标题
**                  6:可设置外圆背景/内圆背景/饼圆三种颜色/刻度尺颜色/文字颜色
**                  7:自适应窗体拉伸,刻度尺和文字自动缩放
**                  8:可自由拓展各种渐变色,各圆的半径
***************************************************************************************************/

#ifndef HPERCENTGAUGE_H
#define HPERCENTGAUGE_H

#include "HAnimationProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPercentGaugePrivate;

class HPercentGauge : public HAnimationProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPercentGauge)
    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int angleStart READ angleStart WRITE setAngleStart)
    Q_PROPERTY(int angleEnd READ angleEnd WRITE setAngleEnd)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor)
    Q_PROPERTY(QColor arcColor READ arcColor WRITE setArcColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor scaleLabelColor READ scaleLabelColor WRITE setScaleLabelColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)
    Q_PROPERTY(QString title READ title WRITE setTitle)


public:
    explicit HPercentGauge(QWidget *parent = nullptr);
    ~HPercentGauge() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int scaleMajor() const;
    int scaleMinor() const;
    int angleStart() const;
    int angleEnd() const;
    QColor background() const;
    QColor baseColor() const;
    QColor arcColor() const;
    QColor scaleColor() const;
    QColor scaleLabelColor() const;
    QColor textColor() const;
    QColor titleColor() const;
    QString title() const;

public slots:
    void setDecimal(int value) override;
    void setScaleMajor(int value);
    void setScaleMinor(int value);
    void setAngleStart(int value);
    void setAngleEnd(int value);
    void setBackground(const QColor &value);
    void setBaseColor(const QColor &value);
    void setArcColor(const QColor &value);
    void setScaleColor(const QColor &value);
    void setScaleLabelColor(const QColor &value);
    void setTextColor(const QColor &value);
    void setTitleColor(const QColor &value);
    void setTitle(const QString &value);

protected:
    HPercentGauge(HPercentGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawArc(QPainter *);
    void drawCircle(QPainter *);
    void drawScale(QPainter *);
    void drawScaleLabel(QPainter *);
    void drawValue(QPainter *);
    void drawTitle(QPainter *);

protected:
    double angleSpan();
    double toAngle(double value);
};

HE_CONTROL_END_NAMESPACE

#endif // HPERCENTGAUGE_H
