#include "HTestSpecDemo_p.h"
#include "HeAlgorithm/HSpecData.h"
#include "HeAlgorithm/HSpecFacade.h"
#include "HeAlgorithm/HMath.h"
#include "HeData/ISpecCalibrate.h"
#include <QtGui/QPolygonF>

HE_ALGORITHM_USE_NAMESPACE

HTestSpecDemo::HTestSpecDemo() :
    HTestSpec(*new HTestSpecDemoPrivate)
{
}

HTestSpecDemo::HTestSpecDemo(HTestSpecDemoPrivate &p) :
    HTestSpec(p)
{
}

HTestSpecDemo::~HTestSpecDemo()
{
}

bool HTestSpecDemo::setSample(QVector<double> value, bool /*avg*/)
{
    Q_D(HTestSpecDemo);
    d->samples[0] = value;
    d->samples[1] = value;
    return d->calcSpec();
}

bool HTestSpecDemo::setEnergy(QPolygonF value, double percent)
{
    Q_D(HTestSpecDemo);
    d->specData->clear();
    d->specData->Energy = HMath::interpolate(value, 380, 780, 0.1);

    if(d->specData->Energy.isEmpty())
        return false;
    d->specFacade->calcSpectrum(d->specData);
    setData("[光谱采样比率]", percent);
    addData("[峰值波长]", d->specData->PeakWave);
    addData("[峰值带宽]", d->specData->Bandwidth);
    addData("[主波长]", d->specData->DominantWave);
    addData("[色纯度]", d->specData->ColorPurity);
    addData("[色温]", d->specData->ColorTemperature);
    addData("[色坐标]", d->specData->CoordinateXy);
    addData("[色坐标x]", d->specData->CoordinateXy.x());
    addData("[色坐标y]", d->specData->CoordinateXy.y());
    addData("[色坐标uv]", d->specData->CoordinateUv);
    addData("[色坐标u]", d->specData->CoordinateUv.x());
    addData("[色坐标v]", d->specData->CoordinateUv.y());
    addData("[色坐标uvp]", d->specData->CoordinateUvp);
    addData("[色坐标up]", d->specData->CoordinateUvp.x());
    addData("[色坐标vp]", d->specData->CoordinateUvp.y());
    addData("[Duv]", d->specData->Duv);
    addData("[明视觉光通量]", d->specData->VisionFlux);
    addData("[红色比]", d->specData->RedRatio);
    addData("[蓝色比]", d->specData->BlueRatio);
    addData("[绿色比]", d->specData->GreenRatio);
    addData("[显色指数]", d->specData->RenderingIndexAvg);
    addData("[显色指数Rx]", d->renderingIndex());
    addData("[光谱光通量]", d->specData->LuminousFlux);
    addData("[光功率]", d->specData->LuminousPower);
    return true;
}

QVector<double> HTestSpecDemo::stdCurve()
{
    Q_D(HTestSpecDemo);
    return d->calibrate->stdCurve();
}
