#ifndef HADJUSTSELECTHANDLER_P_H
#define HADJUSTSELECTHANDLER_P_H

#include "HAdjustSelectHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustSelectHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HAdjustSelectHandlerPrivate();

public:
    IConfigManage *configManage;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTSELECTHANDLER_P_H
