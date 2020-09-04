/***************************************************************************************************
**      2020-09-02  HSeekStyle
**                  参考VLC-3.0.9.2
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QStyleOptionSlider>
#include <QtWidgets/QProxyStyle>

HE_CONTROL_BEGIN_NAMESPACE

class HSeekStyleOption : public QStyleOptionSlider
{
public:
    double buffering = 1.0;
    int length = 0;
    bool animate = false;
    double opacity = 1.0;
    double loading = 0.0;
    QList<qlonglong> points;
};

class HSeekStyle : public QProxyStyle
{
    Q_OBJECT

public:
    explicit HSeekStyle();

public:
    int pixelMetric(PixelMetric metric, const QStyleOption * option = nullptr, const QWidget * widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
};

HE_CONTROL_END_NAMESPACE

