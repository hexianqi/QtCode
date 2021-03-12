#pragma once

#include "HProtocolDemo.h"

class QMutex;
class QLibrary;

class HProtocolDemoPrivate
{
public:
    HProtocolDemoPrivate();

public:
    void loadDll();
    void unloadDLL();

public:
    using FunOpen = bool(*)();
    using FunClose = bool(*)();
    using FunSetIntegralTime = bool(*)(double);
    using FunSetSmooth = bool(*)(int, int);
    using FunGetSpectrumSample = bool(*)(int[], int *, double *, bool);
    using FunGetSpectrumEnergy = bool(*)(double[], int *, double *);
    using FunPelsToWave = double(*)(int);
    using FunSetStdCurve = bool(*)(double[], int);

    FunOpen open;
    FunClose close;
    FunSetIntegralTime setIntegralTime;
    FunSetSmooth setSmooth;
    FunGetSpectrumSample getSpectrumSample;
    FunGetSpectrumEnergy getSpectrumEnergy;
    FunPelsToWave pelsToWave;
    FunSetStdCurve setStdCurve;
    QScopedPointer<QLibrary> lib;

public:
    bool isLoaded = false;
    QMutex *mutex = nullptr;
};
