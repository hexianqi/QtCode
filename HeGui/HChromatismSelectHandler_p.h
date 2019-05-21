#ifndef HCHROMATISMSELECTHANDLER_P_H
#define HCHROMATISMSELECTHANDLER_P_H

#include "HChromatismSelectHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HChromatismSelectHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HChromatismSelectHandlerPrivate();

public:
    IConfigManage *configManage;
};

HE_GUI_END_NAMESPACE

#endif // HCHROMATISMSELECTHANDLER_P_H
