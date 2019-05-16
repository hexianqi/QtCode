#ifndef HPRODUCTINFOEDITHANDLER_P_H
#define HPRODUCTINFOEDITHANDLER_P_H

#include "HProductInfoEditHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeSql/HSqlGlobal.h"

HE_SQL_BEGIN_NAMESPACE
class ISqlHandle;
HE_SQL_END_NAMESPACE
HE_SQL_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HProductInfoEditHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HProductInfoEditHandlerPrivate();

public:
    ISqlHandle *handle;
};

HE_GUI_END_NAMESPACE

#endif // HPRODUCTINFOEDITHANDLER_P_H
