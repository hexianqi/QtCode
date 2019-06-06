#include "HSpecFacade_p.h"
#include "HSpecData.h"
#include "HChromaticity.h"
#include "HChromaticityV2.h"
#include "HPhotopicVision.h"
#include <QtCore/QtMath>

HE_ALGORITHM_BEGIN_NAMESPACE

void calcSpectrumEnergy(HSpecData *data)
{
    if (data->Energy.isEmpty())
        return;

    int i, n, size;
    double x, y, max, total, wave;

    size = data->Energy.size();
    max = 0;
    total = 0;
    n = 0;
    wave = 0;
    for (i = 0; i < size; i++)
    {
        x = data->Energy[i].x();
        y = data->Energy[i].y();
        total += y;
        if (y > max)
        {
            n = i;
            max = y;
            wave = x;
        }
    }

    x = 0;
    for (i = n - 1; i > 1; i--)
    {
        if (data->Energy[i - 1].y() < max / 2 && data->Energy[i + 1].y() > max / 2)
        {
            x = data->Energy[i].x();
            break;
        }
    }
    y = 0;
    for (i = n + 1; i < size - 1; i++)
    {
        if (data->Energy[i - 1].y() > max / 2 && data->Energy[i+1].y() < max / 2)
        {
            y = data->Energy[i].x();
            break;
        }
    }
    data->TotalEnergy = total;
    data->MaxEnergy = max;
    data->PeakWave = wave;
    data->Bandwidth = qFabs(x - y);
    data->EnergyPercent.clear();
    for (auto p : data->Energy)
        data->EnergyPercent.append(QPointF(p.x(), 100 * p.y() / max));
}

HSpecFacadePrivate::HSpecFacadePrivate()
{
    chromaticity = std::shared_ptr<IChromaticity>(new HChromaticity());
    photopicVision = std::make_shared<HPhotopicVision>();
}

void HSpecFacadePrivate::setChromaticity(int type)
{
    if (type == chromaticityType || type < 0 || type > 1)
        return;
    if (type == 0)
        chromaticity.reset(new HChromaticity);
    if (type == 1)
        chromaticity.reset(new HChromaticityV2);
}

HSpecFacade::HSpecFacade()
    : d_ptr(new HSpecFacadePrivate)
{
}

HSpecFacade::~HSpecFacade()
{
}

void HSpecFacade::calcSpectrum(HSpecData *data)
{
    calcSpectrumEnergy(data);
    d_ptr->chromaticity->calcSpectrum(data);
    d_ptr->photopicVision->calcSpectrum(data);
}

void HSpecFacade::setChromaticity(int type)
{
    d_ptr->setChromaticity(type);
}

IChromaticity *HSpecFacade::chromaticity()
{
    return d_ptr->chromaticity.get();
}

HE_ALGORITHM_END_NAMESPACE
