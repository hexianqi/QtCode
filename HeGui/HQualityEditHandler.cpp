#include "HQualityEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HQualityDetailWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IQualityCollection.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQualityEditHandlerPrivate::HQualityEditHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HQualityEditHandler::HQualityEditHandler(QObject *parent) :
    HAbstractGuiHandler(*new HQualityEditHandlerPrivate, parent)
{
}

HQualityEditHandler::~HQualityEditHandler()
{
    qDebug() << __func__;
}

void HQualityEditHandler::initialize(QVariantMap /*param*/)
{
}

QString HQualityEditHandler::typeName()
{
    return "HQualityEditHandler";
}

void HQualityEditHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HQualityEditHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)
    auto widget = new HQualityDetailWidget();
    widget->setData(d->configManage->qualityCollection());
    HListCollectionDialog dlg;
    dlg.setWindowTitle(tr("品质数据配置"));
    dlg.setDataDetailWidget(widget);
    dlg.resize(1200, 600);
    dlg.exec();
    d->model->addAction(ACT_RESET_QUALITY);
}

HE_GUI_END_NAMESPACE
