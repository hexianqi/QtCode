#pragma once

#include "HSqlBrowserHandler.h"
#include "HAbstractGuiHandler_p.h"

HE_BEGIN_NAMESPACE

class HSqlBrowserHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    QString sqlBrowser = "ISpecSqlBrowser";
};

HE_END_NAMESPACE
