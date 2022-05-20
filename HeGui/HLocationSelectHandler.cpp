#include "HLocationSelectHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/ILocationCollection.h"
#include "HePlugin/HSelectDialog.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HLocationSelectHandler::HLocationSelectHandler(QObject *parent) :
    HAbstractConfigHandler(*new HLocationSelectHandlerPrivate, parent)
{
}

HLocationSelectHandler::~HLocationSelectHandler() = default;

QString HLocationSelectHandler::typeName()
{
    return "HLocationSelectHandler";
}

void HLocationSelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HLocationSelectHandler);
    auto data = d->configManage->locationCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptional(data->keys());
    dlg.setCurrentText(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.currentText());
    d->model->addAction(ACT_RESET_LOCATION);
}

HE_END_NAMESPACE
