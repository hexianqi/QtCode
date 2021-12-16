/***************************************************************************************************
**      2018-06-19  HPhotopicVision 明视觉比例系数计算类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HSpecData;

class HPhotopicVision
{
public:
    HPhotopicVision();

public:
    void calcSpectrum(HSpecData *);

protected:
    void readStandard();

protected:
    QPolygonF _standard;
};

HE_END_NAMESPACE
