#include "HTestPlugin.h"
#include "HePlugin/HCie1931ChartView.h"

QWidget *HTestPlugin::testCIE1931View()
{
    return new HCie1931ChartView();
}
