#ifndef HABSTRACTGRADE_P_H
#define HABSTRACTGRADE_P_H

#include "HAbstractGrade.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HAbstractGradePrivate : public HCollectionPrivate<IGradeItem>
{
public:
    HAbstractGradePrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HABSTRACTGRADE_P_H
