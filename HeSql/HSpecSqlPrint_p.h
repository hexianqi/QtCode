#ifndef HSPECSQLPRINT_P_H
#define HSPECSQLPRINT_P_H

#include "HSpecSqlPrint.h"
#include "HAbstractSqlPrint_p.h"

class HSpecDiagramWidget;
class HCIE1931Widget;

HE_SQL_BEGIN_NAMESPACE

class HSpecSqlPrintPrivate : public HAbstractSqlPrintPrivate
{
public:
    HSpecDiagramWidget *specWidget = nullptr;
    HCIE1931Widget *cieWidget = nullptr;
};

HE_SQL_END_NAMESPACE

#endif // HSPECSQLPRINT_P_H
