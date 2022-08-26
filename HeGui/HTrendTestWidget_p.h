#pragma once

#include "HTrendTestWidget.h"
#include "HTestWidget_p.h"

class QActionGroup;
class HDynamicChartView;

HE_BEGIN_NAMESPACE

class ITextStream;
class HSpecEnergyWidget;
class HResultTableWidget;

class HTrendTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HTrendTestWidgetPrivate();

public:
    ITextStream *stream = nullptr;
    HSpecEnergyWidget *energyWidget = nullptr;
    HResultTableWidget *tableWidget = nullptr;
    HDynamicChartView *chartView = nullptr;
    QActionGroup *displayGroup = nullptr;

public:
    double interval = 0.0;
    QString current;
    QStringList optional;
    QStringList displays;
    QStringList selected;
    QList<QVariantMap> result;
    QMap<QString, int> baseY;
};

HE_END_NAMESPACE

