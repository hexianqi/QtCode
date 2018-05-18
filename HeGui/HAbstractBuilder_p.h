#ifndef HABSTRACTBUILDER_P_H
#define HABSTRACTBUILDER_P_H

#include "HAbstractBuilder.h"
#include "HeCommunicate/HCommunicateGlobal.h"
#include "HeController/HControllerGlobal.h"

HE_COMMUNICATE_BEGIN_NAMESPACE
class ICommunicateFactory;
class IDeviceCollection;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IControllerFactory;
class ITestDataFactory;
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HMainWindow;

class HAbstractBuilderPrivate
{
public:
    ICommunicateFactory *communicateFactory = nullptr;
    IControllerFactory *controllerFactory = nullptr;
    ITestDataFactory *testDataFactory = nullptr;
    IDeviceCollection *devices = nullptr;
    IModel *model = nullptr;
    HMainWindow *window = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTBUILDER_P_H
