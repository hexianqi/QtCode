#pragma once

#include "HWeatherGauge.h"
#include "HCircleGauge_p.h"
#include <QtCore/QMap>

HE_BEGIN_NAMESPACE

class HWeatherGaugePrivate : public HCircleGaugePrivate
{
public:
    HWeatherGaugePrivate();

public:
    HWeatherGauge::WeatherType weatherType = HWeatherGauge::WeatherType_Sun;
    QColor negativeColor = QColor(0, 254, 254);
    QColor positiveColor = QColor(215, 5, 5);
    QColor negativeTextColor = QColor(0, 254, 254);
    QColor positiveTextColor = QColor(214, 5, 5);
    QColor negativePixmapColor = QColor(0, 254, 254);
    QColor positivePixmapColor = QColor(214, 5, 5);
    double outerValue = 0;
    double outerMinimum = 0;
    double outerMaximum = 100;
    int outerAngleStart = 0;
    int outerAngleEnd = 0;
    QColor outerRingBackground = QColor(250, 250, 250);
    QColor outerRingColor = QColor(34, 163, 169);
    QColor outerTextColor = QColor(34, 163, 169);
    double outerCurrentValue = 0;

    QMap<HWeatherGauge::WeatherType, QString> svgPaths;
    QPropertyAnimation *outerAnimation = nullptr;
};

HE_END_NAMESPACE
