#ifndef HSPECMODEL_P_H
#define HSPECMODEL_P_H

#include "HSpecModel.h"
#include "HAbstractModel_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestSpec;

class HSpecModelPrivate : public HAbstractModelPrivate
{
public:
    HSpecModelPrivate(HSpecModel *);

public:
    ITestSpec *testSpec;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECMODEL_P_H
