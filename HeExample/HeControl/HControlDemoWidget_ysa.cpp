#include "HControlDemoWidget_p.h"
#include "HGraphicsDemoWidget.h"

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addYSA()
{
    addTab(tr("友善啊"), tr("图形视图框架"), new HGraphicsDemoWidget);
}

HE_END_NAMESPACE
