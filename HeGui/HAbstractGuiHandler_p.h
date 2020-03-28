#ifndef HABSTRACTGUIHANDLER_P_H
#define HABSTRACTGUIHANDLER_P_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class IMainWindow;

class HAbstractGuiHandlerPrivate
{
public:
    HAbstractGuiHandlerPrivate();

public:
    IMainWindow *mainWindow;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTGUIHANDLER_P_H
