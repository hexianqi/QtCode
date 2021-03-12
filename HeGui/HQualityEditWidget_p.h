#pragma once

#include "HQualityEditWidget.h"

class HEntireTableWidget;

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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

HE_GUI_END_NAMESPACE
