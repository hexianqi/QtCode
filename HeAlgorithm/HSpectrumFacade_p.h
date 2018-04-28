#ifndef HSPECTRUMFACADE_P_H
#define HSPECTRUMFACADE_P_H

#include "HSpectrumFacade.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HPhotopicVision;

class HSpectrumFacadePrivate
{
public:
    HSpectrumFacadePrivate();

public:
    void setChromaticity(int type);

public:
    int chromaticityType;
    std::shared_ptr<IChromaticity> chromaticity;
    std::shared_ptr<HPhotopicVision> photopicVision;
};

HE_ALGORITHM_END_NAMESPACE


#endif // HSPECTRUMFACADE_P_H
