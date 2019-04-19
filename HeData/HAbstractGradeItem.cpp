#include "HAbstractGradeItem_p.h"

HE_DATA_BEGIN_NAMESPACE

HAbstractGradeItem::HAbstractGradeItem() :
    HAbstractDataItem(*new HAbstractGradeItemPrivate)
{
    setData("[优先级]", 1);
}

HAbstractGradeItem::HAbstractGradeItem(HAbstractGradeItemPrivate &p) :
    HAbstractDataItem(p)
{
}

HAbstractGradeItem::~HAbstractGradeItem()
{
}

HE_DATA_END_NAMESPACE
