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
    auto func = [=] (QVariantMap)
    {
        HElecCalibrateDialog dlg(d->mainWindow);
        return dlg.exec();
    };
    d->mainWindow->blockAndRun(func);
    d->model->addAction(ACT_RESET_ELEC);
}

HE_END_NAMESPACE
