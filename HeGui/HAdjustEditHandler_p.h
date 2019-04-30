#ifndef HADJUSTEDITHANDLER_P_H
#define HADJUSTEDITHANDLER_P_H

#include "HAdjustEditHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustEditHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HAdjustEditHandlerPrivate();

public:
    IConfigManage *configManage;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITHANDLER_P_H
