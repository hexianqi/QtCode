#pragma once

#include "HAbstractGrade.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HAbstractGradePrivate : public HCollectionPrivate<IGradeItem>
{
public:
    HAbstractGradePrivate();

public:
    IDataFactory *factory = nullptr;
    QVariantMap datas;
};

HE_END_NAMESPACE
