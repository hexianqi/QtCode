#pragma once

#include "HOptionalTableExtend.h"
#include "HAbstractTableExtend_p.h"

class HOptionalTableExtendPrivate : public HAbstractTableExtendPrivate
{
public:
    QStringList display;
    QStringList optional;
    QStringList selected;
};
