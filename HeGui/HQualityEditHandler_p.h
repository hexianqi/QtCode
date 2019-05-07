#ifndef HQUALITYEDITHANDLER_P_H
#define HQUALITYEDITHANDLER_P_H

#include "HQualityEditHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HQualityEditHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HQualityEditHandlerPrivate();

public:
    IConfigManage *configManage;
};

HE_GUI_END_NAMESPACE



#endif // HQUALITYEDITHANDLER_P_H
