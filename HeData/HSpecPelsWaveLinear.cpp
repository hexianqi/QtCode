#include "HSpecPelsWaveLinear_p.h"
#include "HeAlgorithm/HMath.h"

HE_BEGIN_NAMESPACE

HSpecPelsWaveLinear::HSpecPelsWaveLinear() :
    HSpecPelsWave(*new HSpecPelsWaveLinearPrivate)
{
    restoreDefault();
}

HSpecPelsWaveLinear::HSpecPelsWaveLinear(HSpecPelsWaveLinearPrivate &p) :
    HSpecPelsWave(p)
{
}

QString HSpecPelsWaveLinear::typeName()
{
    return "HSpecPelsWaveLinear";
}

double HSpecPelsWaveLinear::handle(double value)
{
    Q_D(HSpecPelsWaveLinear);
    return HMath::interpolate(value, d->points);
}

HE_END_NAMESPACE
