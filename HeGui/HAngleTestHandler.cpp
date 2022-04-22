#include "HAngleTestHandler_p.h"
#include "IMainWindow.h"
#include "HAngleTestWidget.h"
#include "HGuiHelper.h"
#include "HePlugin/HPluginHelper.h"

HE_BEGIN_NAMESPACE

HAngleTestHandler::HAngleTestHandler(QObject *parent) :
    HAbstractGuiHandler(*new HAngleTestHandlerPrivate, parent)
{
}

HAngleTestHandler::~HAngleTestHandler() = default;

QString HAngleTestHandler::typeName()
{
    return "HAngleTestHandler";
}

void HAngleTestHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAngleTestHandler);
    auto w = new HAngleTestWidget;
    auto m = HGuiHelper::decoratorInMainWindow(w, d->mainWindow);
    d->mainWindow->blockAndConnect(m);
    w->start();
    m->show();
    HPluginHelper::centerWidget(m, d->mainWindow);
}

HE_END_NAMESPACE
