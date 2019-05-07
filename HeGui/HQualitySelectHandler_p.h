#ifndef HQUALITYSELECTHANDLER_P_H
#define HQUALITYSELECTHANDLER_P_H

#include "HQualitySelectHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HQualitySelectHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HQualitySelectHandlerPrivate();

public:
    IConfigManage *configManage;
};

HE_GUI_END_NAMESPACE



#endif // HQUALITYSELECTHANDLER_P_H
