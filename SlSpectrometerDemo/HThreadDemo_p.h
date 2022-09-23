#pragma once

#include "HThreadDemo.h"
#include "HeController/HAbstractThread_p.h"

class HSpectrometer;

class HThreadDemoPrivate : public HAbstractThreadPrivate
{
public:
    HThreadDemoPrivate();
    ~HThreadDemoPrivate();

public:
    HSpectrometer *spectrometer;
};



