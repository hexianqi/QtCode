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
    auto func = [=] (QVariantMap)
    {
        HLuminousCalibrateDialog dlg(d->mainWindow);
        return dlg.exec();
    };
    d->mainWindow->blockAndRun(func);
    d->model->addAction(ACT_RESET_LUMINOUS);
}

HE_END_NAMESPACE
