/***************************************************************************************************
**      2019-07-11  HCircleGauge 圆形仪表盘
***************************************************************************************************/

#ifndef HCIRCLEGAUGE_H
#define HCIRCLEGAUGE_H

#include "HAnimationProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCircleGaugePrivate;

class HCircleGauge : public HAnimationProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCircleGauge)
    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int scaleDecimal READ scaleDecimal WRITE setScaleDecimal)
    Q_PROPERTY(int angleStart READ angleStart WRITE setAngleStart)
    Q_PROPERTY(int angleEnd READ angleEnd WRITE setAngleEnd)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor scaleLabelColor READ scaleLabelColor WRITE setScaleLabelColor)

public:
    explicit HCircleGauge(QWidget *parent = nullptr);
    ~HCircleGauge() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int scaleMajor() const;
    int scaleMinor() const;
    int scaleDecimal() const;
    int angleStart() const;
    int angleEnd() const;
    QColor background() const;
    QColor textColor() const;
    QColor pointerColor() const;
    QColor scaleColor() const;
    QColor scaleLabelColor() const;

public slots:
    void setDecimal(int value) override;
    void setScaleMajor(int value);
    void setScaleMinor(int value);
    void setScaleDecimal(int value);
    void setAngleStart(int value);
    void setAngleEnd(int value);
    void setBackground(const QColor &value);
    void setTextColor(const QColor &value);
    void setPointerColor(const QColor &value);
    void setScaleColor(const QColor &value);
    void setScaleLabelColor(const QColor &value);

protected:
    HCircleGauge(HCircleGaugePrivate &p, QWidget *parent = nullptr);

protected:
    virtual void preDraw(QPainter *);
    virtual void drawBackground(QPainter *);
    virtual void drawProgress(QPainter *, int radius) = 0;
    virtual void drawScale(QPainter *, int radius);
    virtual void drawScaleLabel(QPainter *, int radius);
    virtual void drawPointer(QPainter *, int radius);
    virtual void drawValue(QPainter *, int radius);
    double angleSpan();
    double toAngle(double value);
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCLEGAUGE_H
