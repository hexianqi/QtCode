#include "HSpecCalibrateHandler_p.h"
#include "IMainWindow.h"
#include "HSpecCalibrateDialog.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HSpecCalibrateHandler::HSpecCalibrateHandler(QObject *parent) :
    HAbstractConfigHandler(*new HSpecCalibrateHandlerPrivate, parent)
{
}

HSpecCalibrateHandler::~HSpecCalibrateHandler() = default;

QString HSpecCalibrateHandler::typeName()
{
    return "HSpecCalibrateHandler";
}

void HSpecCalibrateHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HSpecCalibrateHandler);
    HSpecCalibrateDialog dlg(d->mainWindow);
    d->mainWindow->blockAndRun(&dlg);
    d->model->addAction(ACT_RESET_SPECTRUM);
}

HE_END_NAMESPACE
