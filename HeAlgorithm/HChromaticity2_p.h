#pragma once

#include "HChromaticity2.h"
#include "HChromaticity_p.h"

HE_BEGIN_NAMESPACE

class HChromaticity2Private : public HChromaticityPrivate
{
public:
    HChromaticity2Private();

public:
    std::shared_ptr<HCieUcs> cieUcs;
};

HE_END_NAMESPACE
