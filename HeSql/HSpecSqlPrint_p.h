#pragma once

#include "HSpecSqlPrint.h"
#include "HAbstractSqlPrint_p.h"

class HSpecDiagramWidget;
class HCie1931Widget;

HE_SQL_BEGIN_NAMESPACE

class HSpecSqlPrintPrivate : public HAbstractSqlPrintPrivate
{
public:
    HSpecDiagramWidget *specWidget = nullptr;
    HCie1931Widget *cieWidget = nullptr;
};

HE_SQL_END_NAMESPACE
