#include "HControlDemoWidget_p.h"
#include "HFlatStyleWidget.h"
#include "HQssStyleWindow.h"

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addStyle()
{
    addTab(tr("样式"), "Flat", new HFlatStyleWidget);
    addTab(tr("样式"), "Qss", new HQssStyleWindow);
}

HE_END_NAMESPACE
