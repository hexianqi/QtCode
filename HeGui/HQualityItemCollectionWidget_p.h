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
    QStringList optional;
    QStringList selected;
    QStringList unselected;
};

HE_END_NAMESPACE
