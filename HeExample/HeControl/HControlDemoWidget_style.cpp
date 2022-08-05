#include "HControlDemoWidget_p.h"
#include "HFlatStyleWidget.h"

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addStyle()
{
    addTab(tr("样式"), "Flat", new HFlatStyleWidget);
}

HE_END_NAMESPACE
