#include "HElecCalibrateHandler_p.h"
#include "IMainWindow.h"
#include "HElecCalibrateDialog.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HElecCalibrateHandler::HElecCalibrateHandler(QObject *parent) :
    HAbstractConfigHandler(*new HElecCalibrateHandlerPrivate, parent)
{
}

HElecCalibrateHandler::~HElecCalibrateHandler() = default;

QString HElecCalibrateHandler::typeName()
{
    return "HElecCalibrateHandler";
}

void HElecCalibrateHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HElecCalibrateHandler);
    HElecCalibrateDialog dlg(d->mainWindow);
    d->mainWindow->openDialog(&dlg);
    d->model->addAction(ACT_RESET_ELEC);
}

HE_END_NAMESPACE
