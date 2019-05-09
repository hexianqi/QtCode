#ifndef HSQLTABLEVIEW_P_H
#define HSQLTABLEVIEW_P_H

#include "HSqlTableView.h"
#include "HePlugin/HTableView_p.h"

class HOptionalTableExtend;

HE_SQL_BEGIN_NAMESPACE

class HSqlTableViewPrivate : public HTableViewPrivate
{
public:
    HOptionalTableExtend *optionalExtend;
};

HE_SQL_END_NAMESPACE

#endif // HSQLTABLEVIEW_P_H
