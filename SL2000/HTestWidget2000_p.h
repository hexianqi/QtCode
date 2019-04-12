#ifndef HTESTWIDGET2000_P_H
#define HTESTWIDGET2000_P_H

#include "HTestWidget2000.h"
#include "HeGui/HTestWidget_p.h"

class HCIE1931Widget;

HE_GUI_BEGIN_NAMESPACE
class HSpecEnergyWidget;
class HResultTableWidget;
class ITestSetWidget;
class IDetailWidget;
HE_GUI_END_NAMESPACE

class HTestWidget2000Private : public HTestWidgetPrivate
{
public:
    HTestWidget2000Private();

public:
    HSpecEnergyWidget *energyWidget;
    HCIE1931Widget *cieWidget;
    HResultTableWidget *resultWidget;
    ITestSetWidget *testSetWidget;
    IDetailWidget *detailWidget;

public:
    QStringList resultOptionals;

public:
    QAction *actionClear;
};

#endif // HTESTWIDGET2000_P_H
