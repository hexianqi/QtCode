#include "HAdjustSelectHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjustCollection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"

HE_BEGIN_NAMESPACE

HAdjustSelectHandler::HAdjustSelectHandler(QObject *parent) :
    HAbstractConfigHandler(*new HAdjustSelectHandlerPrivate, parent)
{
}

HAdjustSelectHandler::~HAdjustSelectHandler() = default;

QString HAdjustSelectHandler::typeName()
{
    return "HAdjustSelectHandler";
}

void HAdjustSelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAdjustSelectHandler);
    auto data = d->configManage->adjustCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptional(data->keys());
    dlg.setCurrentText(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.currentText());
    d->model->addAction(ACT_RESET_ADJUST);
}

HE_END_NAMESPACE
