#ifndef HCHROMATISMEDITHANDLER_P_H
#define HCHROMATISMEDITHANDLER_P_H

#include "HChromatismEditHandler.h"

#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HChromatismEditHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HChromatismEditHandlerPrivate();

public:
    IConfigManage *configManage;
};

HE_GUI_END_NAMESPACE

#endif // HCHROMATISMEDITHANDLER_P_H
