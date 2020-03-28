#ifndef HABSTRACTCONFIGHANDLER_P_H
#define HABSTRACTCONFIGHANDLER_P_H

#include "HAbstractConfigHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"
#include "HeController/HControllerGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAbstractConfigHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HAbstractConfigHandlerPrivate();

public:
    IConfigManage *configManage;
    IModel *model;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTCONFIGHANDLER_P_H
