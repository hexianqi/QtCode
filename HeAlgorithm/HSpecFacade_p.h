#pragma once

#include "HSpecFacade.h"
#include <memory>

HE_BEGIN_NAMESPACE

class HPhotopicVision;

class HSpecFacadePrivate
{
public:
    HSpecFacadePrivate();

public:
    void setChromaticity(int type);

public:
    int chromaticityType = 1;
    std::shared_ptr<IChromaticity> chromaticity;
    std::shared_ptr<HPhotopicVision> photopicVision;
};

HE_END_NAMESPACE
