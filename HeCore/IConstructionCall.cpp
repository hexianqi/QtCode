#include "IConstructionCall.h"

HE_BEGIN_NAMESPACE

HConstructionCallHelper::HConstructionCallHelper() :
    _p(nullptr)
{
}

HConstructionCallHelper::~HConstructionCallHelper()
{
    if (_p)
        _p->initialize();
}

void HConstructionCallHelper::initialize(IConstructionCall *p) const
{
    _p = p;
}

HE_END_NAMESPACE
