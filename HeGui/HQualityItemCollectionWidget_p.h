#pragma once

#include "HQualityItemCollectionWidget.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HQualityItemCollectionPrivate
{
public:
    HQualityItemCollectionPrivate();

public:
    IDataFactory *factory = nullptr;
    IQualityItemCollection *data = nullptr;
    QStringList optionals;
    QStringList selecteds;
    QStringList unselecteds;
};

HE_END_NAMESPACE
