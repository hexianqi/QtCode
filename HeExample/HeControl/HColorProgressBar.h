/***************************************************************************************************
**      2019-06-19  HColorProgressBar 带颜色进度条控件。
***************************************************************************************************/

#pragma once

#include "HAbstractProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HColorProgressBarPrivate;

class HColorProgressBar : public HAbstractProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HColorProgressBar)

    Q_PROPERTY(int radius READ radius WRITE setRadius)
    Q_PROPERTY(TextPosition textPosition READ textPosition WRITE setTextPosition)
    Q_PROPERTY(QColor textForeColor READ textForeColor WRITE setTextForeColor)
    Q_PROPERTY(QColor textBackColor READ textBackColor WRITE setTextBackColor)
    Q_PROPERTY(BarStyle barStyle READ barStyle WRITE setBarStyle)
    Q_PROPERTY(QColor barForeColor READ barForeColor WRITE setBarForeColor)
    Q_PROPERTY(QColor barForeAlternateColor READ barForeAlternateColor WRITE setBarForeAlternateColor)
    Q_PROPERTY(QColor barBackColor READ barBackColor WRITE setBarBackColor)
    Q_PROPERTY(int barStepSpace READ barStepSpace WRITE setBarStepSpace)
    Q_PROPERTY(int barStepDelta READ barStepDelta WRITE setBarStepDelta)
    Q_PROPERTY(int barStepSize READ barStepSize WRITE setBarStepSize)

public:
    enum TextPosition
    {
        TextPosition_InBar,
        TextPosition_OnBar,
        TextPosition_OutBar
    };
    Q_ENUM(TextPosition)

    enum BarStyle
    {
        BarStyle_Solid,
        BarStyle_Gradual,
        BarStyle_Segmented
    };
    Q_ENUM(BarStyle)

public:
    explicit HColorProgressBar(QWidget *parent = nullptr);

public:
    QSize sizeHint() const override;
    int radius() const;
    TextPosition textPosition() const;
    QColor textForeColor() const;
    QColor textBackColor() const;
    BarStyle barStyle() const;
    QColor barForeColor() const;
    QColor barForeAlternateColor() const;
    QColor barBackColor() const;
    int barStepSpace() const;
    int barStepDelta() const;
    int barStepSize() const;

public slots:
    void setRadius(int value);
    void setTextPosition(TextPosition value);
    void setTextForeColor(const QColor &value);
    void setTextBackColor(const QColor &value);
    void setBarStyle(BarStyle value);
    void setBarForeColor(const QColor &value);
    void setBarForeAlternateColor(const QColor &value);
    void setBarBackColor(const QColor &value);
    void setBarStepSpace(int value);
    void setBarStepDelta(int value);
    void setBarStepSize(int value);
    void setBarForeDataColors(const QGradientStops &value);

protected:
    HColorProgressBar(HColorProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBarBackground(QPainter *, QRectF rect);
    void drawTextBackground(QPainter *, QRectF rect);
    void drawData(QPainter *, QRectF rect);
    void drawBarStep(QPainter *, QRectF rect);
    void drawText(QPainter *, QRectF rect);
};

HE_CONTROL_END_NAMESPACE
