#ifndef HSPECELECMODEL_P_H
#define HSPECELECMODEL_P_H

#include "HSpecElecModel.h"
#include "HAbstractModel_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
class ITestElec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecElecModelPrivate : public HAbstractModelPrivate
{
public:
    HSpecElecModelPrivate();

public:
    ITestSpec *testSpec = nullptr;
    ITestElec *testElec = nullptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECELECMODEL_P_H
