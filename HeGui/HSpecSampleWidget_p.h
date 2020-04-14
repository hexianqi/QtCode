#ifndef HSPECSAMPLEWIDGET_P_H
#define HSPECSAMPLEWIDGET_P_H

#include "HSpecSampleWidget.h"
#include "HeData/HDataGlobal.h"
#include "HePlugin/HVernierWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecSampleWidgetPrivate : public HVernierWidgetPrivate
{
public:
    HSpecSampleWidgetPrivate();

public:
    ITestSpec *testSpec;

public:
    bool enablePeak = true;
    QList<bool> curveVisibles;
    QList<double> verniers;
};

HE_GUI_END_NAMESPACE

#endif // HSPECSAMPLEWIDGET_P_H
