#pragma once

#include "HAbstractGrade.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HAbstractGradePrivate : public HCollectionPrivate<IGradeItem>
{
public:
    HAbstractGradePrivate();

public:
    IDataFactory *factory = nullptr;
    QVariantMap datas;
};

HE_DATA_END_NAMESPACE
