#include "HImportDeviceHandler_p.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HImportDeviceHandler::HImportDeviceHandler(QObject *parent) :
    HAbstractConfigHandler(*new HImportDeviceHandlerPrivate, parent)
{
}

HImportDeviceHandler::~HImportDeviceHandler()
{
}

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

HE_GUI_END_NAMESPACE
