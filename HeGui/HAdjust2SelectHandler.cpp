#include "HAdjust2SelectHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjust2Collection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"

HE_BEGIN_NAMESPACE

HAdjust2SelectHandler::HAdjust2SelectHandler(QObject *parent) :
    HAbstractConfigHandler(*new HAdjust2SelectHandlerPrivate, parent)
{
}

HAdjust2SelectHandler::~HAdjust2SelectHandler() = default;

QString HAdjust2SelectHandler::typeName()
{
    return "HAdjust2SelectHandler";
}

void HAdjust2SelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAdjust2SelectHandler);
    auto data = d->configManage->adjust2Collection();
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
