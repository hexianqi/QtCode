#ifndef HMODELSPEC_P_H
#define HMODELSPEC_P_H

#include "HModelSpec.h"
#include "HeController/HAbstractModel_p.h"
#include "HeGui/HGuiGlobal.h"

HE_GUI_BEGIN_NAMESPACE
class HSpecCalibrateWidget;
HE_GUI_END_NAMESPACE
HE_GUI_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE

class HModelSpecPrivate : public HAbstractModelPrivate
{
public:
    HModelSpecPrivate(IModel *);

public:
    HSpecCalibrateWidget *widget();

public:
    ITestSpec *testSpec = nullptr;
    HSpecCalibrateWidget *testWidget = nullptr;
};

#endif // HMODELSPEC_P_H
