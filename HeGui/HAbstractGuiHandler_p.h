#ifndef HABSTRACTGUIHANDLER_P_H
#define HABSTRACTGUIHANDLER_P_H

#include "HAbstractGuiHandler.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IMainWindow;

class HAbstractGuiHandlerPrivate
{
public:
    HAbstractGuiHandlerPrivate();

public:
    IMainWindow *mainWindow;
    IModel *model;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTGUIHANDLER_P_H
