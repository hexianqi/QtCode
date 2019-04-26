#ifndef HGRADESELECTHANDLER_P_H
#define HGRADESELECTHANDLER_P_H

#include "HGradeSelectHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HGradeSelectHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HGradeSelectHandlerPrivate();

public:
    IConfigManage *configManage;
};

HE_GUI_END_NAMESPACE

#endif // HGRADESELECTHANDLER_P_H
