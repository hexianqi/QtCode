#include "HCallorHelper.h"

HE_CORE_BEGIN_NAMESPACE

HCallorHelper::HCallorHelper()
    : _p(nullptr)
{
}

HCallorHelper::~HCallorHelper()
{
    if (_p)
        _p->initialize();
}

void HCallorHelper::initialize(IConstructorCall *p) const
{
    _p = p;
}

HE_CORE_END_NAMESPACE
