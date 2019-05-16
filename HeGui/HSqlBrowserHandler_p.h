#ifndef HSQLBROWSERHANDLER_P_H
#define HSQLBROWSERHANDLER_P_H

#include "HSqlBrowserHandler.h"
#include "HAbstractGuiHandler_p.h"
#include "HeSql/HSqlGlobal.h"

HE_SQL_BEGIN_NAMESPACE
class ISqlBrowser;
HE_SQL_END_NAMESPACE
HE_SQL_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSqlBrowserHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HSqlBrowserHandlerPrivate();

public:
    ISqlBrowser *browser;
};

HE_GUI_END_NAMESPACE

#endif // HSQLBROWSERHANDLER_P_H
