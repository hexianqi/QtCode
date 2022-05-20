#include "HQualityEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HQualityEditWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IQualityCollection.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HQualityEditHandler::HQualityEditHandler(QObject *parent) :
    HAbstractConfigHandler(*new HQualityEditHandlerPrivate, parent)
{
}

HQualityEditHandler::~HQualityEditHandler() = default;

void HQualityEditHandler::initialize(QVariantMap param)
{
    Q_D(HQualityEditHandler);
    if (param.contains("key"))
        d->key = param.value("key").toString();
    if (param.contains("optional"))
        d->optional = param.value("optional").toString();
}

QString HQualityEditHandler::typeName()
{
    return "HQualityEditHandler";
}

void HQualityEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HQualityEditHandler);
    auto widget = new HQualityEditWidget;
    if (!d->optional.isEmpty())
        widget->setOptional(HAppContext::getContextValue<QStringList>(d->optional));
    HDataDetail<IQuality> detail;
    detail.setEditer(widget);
    detail.setData(d->configManage->qualityCollection(d->key));
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("品质数据配置"));
    dlg.setDataDetail(&detail);
    dlg.resize(1200, 600);
    dlg.exec();
    d->model->addAction(ACT_RESET_QUALITY);
}

HE_END_NAMESPACE
