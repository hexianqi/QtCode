#include "HQualitySelectHandler_p.h"
#include "IMainWindow.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IQualityCollection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQualitySelectHandlerPrivate::HQualitySelectHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HQualitySelectHandler::HQualitySelectHandler(QObject *parent) :
    HAbstractGuiHandler(*new HQualitySelectHandlerPrivate, parent)
{
}

HQualitySelectHandler::~HQualitySelectHandler()
{
    qDebug() << __func__;
}

void HQualitySelectHandler::initialize(QVariantMap /*param*/)
{
}

QString HQualitySelectHandler::typeName()
{
    return "HQualitySelectHandler";
}

void HQualitySelectHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HQualitySelectHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)

    auto data = d->configManage->qualityCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptionals(data->keys());
    dlg.setSelected(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.selected());
    d->model->addAction(ACT_RESET_QUALITY);
}

HE_GUI_END_NAMESPACE
