#include "HControlDemoWidget_p.h"
#include "HUiDemo01Widget.h"
#include "HUiDemo02Widget.h"
#include "HUiDemo03Widget.h"

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addUI()
{
    addTab(tr("界面"), "01", new HUiDemo01Widget);
    addTab(tr("界面"), "02", new HUiDemo02Widget);
    addTab(tr("界面"), "03", new HUiDemo03Widget);
}

HE_END_NAMESPACE
