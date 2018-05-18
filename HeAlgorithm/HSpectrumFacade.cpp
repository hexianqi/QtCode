#include "HSpectrumFacade_p.h"
#include "ISpectrumData.h"
#include "HChromaticity.h"
#include "HChromaticityV2.h"
#include "HPhotopicVision.h"
#include <QtMath>

HE_ALGORITHM_BEGIN_NAMESPACE

void calcSpectrumEnergy(QPolygonF poly, double &totalEnergy, double &maxEnergy, double &peakWave, double &bandwidth)
{
    if(poly.isEmpty())
        return;

    int i,peak,size;
    double x,y;

    peak = 0;
    size = poly.size();
    maxEnergy = 0;
    totalEnergy = 0;
    for (i = 0; i < size; i++)
    {
        x = poly[i].x();
        y = poly[i].y();
        totalEnergy += y;
        if (y > maxEnergy)
        {
            peak = i;
            maxEnergy = y;
            peakWave = x;
        }
    }
    x = 0;
    y = 0;
    for (i = peak - 1; i > 1; i--)
    {
        if (poly[i-1].y() < maxEnergy / 2 && poly[i+1].y() > maxEnergy / 2)
        {
            x = poly[i].x();
            break;
        }
    }
    for (i = peak + 1; i < size - 1; i++)
    {
        if (poly[i-1].y() > maxEnergy / 2 && poly[i+1].y() < maxEnergy / 2)
        {
            y = poly[i].x();
            break;
        }
    }
    bandwidth = qFabs(x - y);
}

HSpectrumFacadePrivate::HSpectrumFacadePrivate()
{
    chromaticity = std::shared_ptr<HChromaticity>(new HChromaticity());
    photopicVision = std::make_shared<HPhotopicVision>();
}

void HSpectrumFacadePrivate::setChromaticity(int type)
{
    if (type == chromaticityType || type < 0 || type > 2)
        return;
    if (type == 0)
        chromaticity.reset(new HChromaticity);
    if (type == 1)
        chromaticity.reset(new HChromaticityV2);
}

HSpectrumFacade::HSpectrumFacade()
    : d_ptr(new HSpectrumFacadePrivate)
{
}

HSpectrumFacade::~HSpectrumFacade()
{
}

void HSpectrumFacade::calcSpectrum(ISpectrumData *sp)
{
    calcSpectrumEnergy(sp->Energy, sp->TotalEnergy, sp->MaxEnergy, sp->PeakWave, sp->Bandwidth);
    d_ptr->chromaticity->calcSpectrum(sp);
    d_ptr->photopicVision->calcVisionRatio(sp->Energy, sp->EnergyRatio, sp->RedRatio, sp->GreenRadio, sp->BlueRatio);
    sp->VisionEnergy = d_ptr->photopicVision->calcVisionEnergy(sp->Energy);
}

void HSpectrumFacade::setChromaticity(int type)
{
    d_ptr->setChromaticity(type);
}

std::shared_ptr<IChromaticity> HSpectrumFacade::getChromaticity()
{
    return d_ptr->chromaticity;
}

HE_ALGORITHM_END_NAMESPACE
