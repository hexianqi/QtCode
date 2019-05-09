#ifndef HOPTIONALTABLEEXTEND_P_H
#define HOPTIONALTABLEEXTEND_P_H

#include "HOptionalTableExtend.h"
#include "HAbstractTableExtend_p.h"

class HOptionalTableExtendPrivate : public HAbstractTableExtendPrivate
{
public:
    QStringList displays;
    QStringList optionals;
    QStringList selecteds;
};

#endif // HOPTIONALTABLEEXTEND_P_H
