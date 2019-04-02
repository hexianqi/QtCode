#include "HTestPlugin.h"
#include "HePlugin/HCIE1931ChartView.h"

QWidget *HTestPlugin::testCIE1931View()
{
    return new HCIE1931ChartView();
}
