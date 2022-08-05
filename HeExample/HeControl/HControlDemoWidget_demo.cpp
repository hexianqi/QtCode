#include "HControlDemoWidget_p.h"
#include "HStandardPixmapWidget.h"
#include "HLogDemoWidget.h"
#include "HRunTimeDemoWidget.h"
#include "HSmoothCurveDemoWidget.h"



#include "HStyleWidget.h"
#include "HQssCreator.h"
#include "HIconFontWidget.h"
#include "HSpliteWidget.h"

HE_BEGIN_NAMESPACE

void HControlDemoWidget::addDemo()
{
    addTab(tr("DEMO"), tr("Qt内置图标"),      new HStandardPixmapWidget);
    addTab(tr("DEMO"), tr("日志重定向"),      new HLogDemoWidget);
    addTab(tr("DEMO"), tr("运行时间记录"),    new HRunTimeDemoWidget);
    addTab(tr("DEMO"), tr("平滑曲线"),        new HSmoothCurveDemoWidget);




    addTab(tr("DEMO"), "Style", new HStyleWidget);
    addTab(tr("DEMO"), "Qss", new HQssCreator);
    addTab(tr("DEMO"), tr("字体图标"), new HIconFontWidget);
    addTab(tr("DEMO"), tr("分割界面"), new HSpliteWidget);
}

HE_END_NAMESPACE
