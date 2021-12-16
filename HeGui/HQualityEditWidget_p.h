#pragma once

#include "HQualityEditWidget.h"

class HEntireTableWidget;

HE_BEGIN_NAMESPACE

class IDataFactory;
class HQualityItemCollectionWidget;

class HQualityEditWidgetPrivate
{
public:
    HQualityEditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IQuality *data = nullptr;
    QColor colorInvalidData = Qt::white;
    QColor colorDamage = Qt::white;
    QColor colorNoPass = Qt::white;
    QColor colorPassing = Qt::white;
    HQualityItemCollectionWidget *widget1 = nullptr;
    HQualityItemCollectionWidget *widget2 = nullptr;
    QString css;
};

HE_END_NAMESPACE
