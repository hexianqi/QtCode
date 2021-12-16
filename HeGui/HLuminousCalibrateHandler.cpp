#include "HLuminousCalibrateHandler_p.h"
#include "IMainWindow.h"
#include "HLuminousCalibrateDialog.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HLuminousCalibrateHandler::HLuminousCalibrateHandler(QObject *parent) :
    HAbstractConfigHandler(*new HLuminousCalibrateHandlerPrivate, parent)
{
}

HLuminousCalibrateHandler::~HLuminousCalibrateHandler() = default;

QString HLuminousCalibrateHandler::typeName()
{
    return "HLuminousCalibrateHandler";
}

void HLuminousCalibrateHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HLuminousCalibrateHandler);
    HLuminousCalibrateDialog dlg(d->mainWindow);
    d->mainWindow->openDialog(&dlg);
    d->model->addAction(ACT_RESET_ELEC);
    d->model->addAction(ACT_RESET_LUMINOUS);
}

HE_END_NAMESPACE
