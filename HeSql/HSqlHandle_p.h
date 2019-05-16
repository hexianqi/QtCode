#ifndef HSQLHANDLE_P_H
#define HSQLHANDLE_P_H

#include "HSqlHandle.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlHandlePrivate
{
public:
    ISqlTableModel *model = nullptr;
    IProductInfo *productInfo = nullptr;
    QStringList fieldFinds;
};

HE_SQL_END_NAMESPACE

#endif // HSQLHANDLE_P_H
