#ifndef HSPECELECMODEL_P_H
#define HSPECELECMODEL_P_H

#include "HSpecElecModel.h"
#include "HSpecModel_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestElec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecElecModelPrivate : public HSpecModelPrivate
{
public:
    HSpecElecModelPrivate(IModel *);

public:
    ITestElec *testElec;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECELECMODEL_P_H
