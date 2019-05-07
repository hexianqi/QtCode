#ifndef HQUALITYEDITWIDGET_P_H
#define HQUALITYEDITWIDGET_P_H

#include "HQualityEditWidget.h"

class HEntireTableWidget;

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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
    QStringList optionals;
    QMap<IQuality::QualityType, QStringList> selecteds;
    QMap<IQuality::QualityType, QStringList> unselecteds;
    QMap<IQuality::QualityType, HEntireTableWidget *> tableWidgets;
};

HE_GUI_END_NAMESPACE




#endif // HQUALITYEDITWIDGET_P_H
