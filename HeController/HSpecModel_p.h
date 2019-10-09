#ifndef HSPECMODEL_P_H
#define HSPECMODEL_P_H

#include "HSpecModel.h"
#include "HAbstractModel_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecModelPrivate : public HAbstractModelPrivate
{
public:
    HSpecModelPrivate(IModel *);

public:
    ITestSpec *testSpec;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECMODEL_P_H
