#ifndef HCHROMATISMEDITWIDGET_P_H
#define HCHROMATISMEDITWIDGET_P_H

#include "HChromatismEditWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HChromatismEditWidgetPrivate
{
public:
    HChromatismEditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IChromatism *data = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HCHROMATISMEDITWIDGET_P_H
