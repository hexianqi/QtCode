#include "HSpecPelsWavePolynom_p.h"
#include "HeAlgorithm/HMultiFit.h"

HE_BEGIN_NAMESPACE

HSpecPelsWavePolynom::HSpecPelsWavePolynom() :
    HSpecPelsWave(*new HSpecPelsWavePolynomPrivate)
{
    restoreDefault();
}

HSpecPelsWavePolynom::HSpecPelsWavePolynom(HSpecPelsWavePolynomPrivate &p) :
    HSpecPelsWave(p)
{
}

QString HSpecPelsWavePolynom::typeName()
{
    return "HSpecPelsWavePolynom";
}

void HSpecPelsWavePolynom::restoreDefault()
{
    setData("[光谱象元波长多项式项数]", 3);
    HSpecPelsWave::restoreDefault();
}

void HSpecPelsWavePolynom::setPoints(const QPolygonF &value)
{
    HSpecPelsWave::setPoints(value);
    if (data("[光谱象元波长多项式项数]").toInt() > value.size())
        setData("[光谱象元波长多项式项数]", value);
    linear();
}

double HSpecPelsWavePolynom::handle(double value)
{
    return linearEst(value);
}

void HSpecPelsWavePolynom::linear()
{
    Q_D(HSpecPelsWavePolynom);
    double chisq;
    d->ca.clear();
    d->cova.clear();
    d->ca.resize(data("[光谱象元波长多项式项数]").toInt());
    HMultiFit::linear(d->points, d->ca, d->cova, &chisq);
}

double HSpecPelsWavePolynom::linearEst(double value)
{
    Q_D(HSpecPelsWavePolynom);
    if (d->ca.size() < 2)
        return 0.0;
    double y, error;
    HMultiFit::linear_est(value, d->ca, d->cova, &y, &error);
    return  y;
}

HE_END_NAMESPACE
