#pragma once

#include "HQualityItemCollectionWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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

HE_GUI_END_NAMESPACE
