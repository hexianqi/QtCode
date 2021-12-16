#include "HImportDeviceHandler_p.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HImportDeviceHandler::HImportDeviceHandler(QObject *parent) :
    HAbstractConfigHandler(*new HImportDeviceHandlerPrivate, parent)
{
}

HImportDeviceHandler::~HImportDeviceHandler() = default;

QString HImportDeviceHandler::typeName()
{
    return "HImportDeviceHandler";
}

void HImportDeviceHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HImportDeviceHandler);
    d->model->addAction(ACT_GET_RAM);
    d->model->addAction(ACT_RESET_SPECTRUM);
}

HE_END_NAMESPACE
