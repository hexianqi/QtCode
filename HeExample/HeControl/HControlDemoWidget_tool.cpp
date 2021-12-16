#include "HControlDemoWidget_p.h"
#include "HCodeCountWidget.h"
#include "HEmailWidget.h"
#include "HNetworkWidget.h"
#include "HPngAmend.h"
#include "HSerialPortWidget.h"

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addTool()
{
    addTab(tr("工具"), new HCodeCountWidget);
    addTab(tr("工具"), new HEmailWidget);
    addTab(tr("工具"), new HNetworkWidget);
    addTab(tr("工具"), new HPngAmend);
    addTab(tr("工具"), new HSerialPortWidget);
}

HE_END_NAMESPACE
