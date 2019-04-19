#include "HAbstractGrade_p.h"

HE_DATA_BEGIN_NAMESPACE

HAbstractGrade::HAbstractGrade() :
    HCollection<IGradeItem>(*new HAbstractGradePrivate)
{
}

HAbstractGrade::HAbstractGrade(HAbstractGradePrivate &p) :
    HCollection<IGradeItem>(p)
{
}

HAbstractGrade::~HAbstractGrade()
{
}

HE_DATA_END_NAMESPACE
