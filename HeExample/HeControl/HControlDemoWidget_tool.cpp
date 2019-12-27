#include "HControlDemoWidget_p.h"
#include "HCodeCountWidget.h"
#include "HNetworkWidget.h"
#include "HPngAmend.h"
#include "HEmailWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

void HControlDemoWidget::addTool()
{
    addTab(tr("工具"), new HCodeCountWidget);
    addTab(tr("工具"), new HNetworkWidget);
    addTab(tr("工具"), new HPngAmend);
    addTab(tr("工具"), new HEmailWidget);
}

HE_CONTROL_END_NAMESPACE
