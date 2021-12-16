#pragma once

#include "HSqlTableView.h"
#include "HePlugin/HTableView_p.h"

class HOptionalTableExtend;

HE_BEGIN_NAMESPACE

class HSqlTableViewPrivate : public HTableViewPrivate
{
public:
    HOptionalTableExtend *optionalExtend;
};

HE_END_NAMESPACE
