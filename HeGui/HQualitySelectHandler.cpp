#include "HQualitySelectHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/IQualityCollection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"

HE_BEGIN_NAMESPACE

HQualitySelectHandler::HQualitySelectHandler(QObject *parent) :
    HAbstractConfigHandler(*new HQualitySelectHandlerPrivate, parent)
{
}

HQualitySelectHandler::~HQualitySelectHandler() = default;

QString HQualitySelectHandler::typeName()
{
    return "HQualitySelectHandler";
}

void HQualitySelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HQualitySelectHandler);
    auto data = d->configManage->qualityCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptionals(data->keys());
    dlg.setCurrentText(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.currentText());
    d->model->addAction(ACT_RESET_QUALITY);
}

HE_END_NAMESPACE
