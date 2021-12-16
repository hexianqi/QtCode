#include "HExportDeviceHandler_p.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HExportDeviceHandler::HExportDeviceHandler(QObject *parent) :
    HAbstractConfigHandler(*new HExportDeviceHandlerPrivate, parent)
{
}

HExportDeviceHandler::~HExportDeviceHandler() = default;

QString HExportDeviceHandler::typeName()
{
    return "HExportDeviceHandler";
}

void HExportDeviceHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HExportDeviceHandler);
    d->model->addAction(ACT_SET_RAM);
}

HE_END_NAMESPACE
