#include "HAdjustEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HAdjustDetailWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjustCollection.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustEditHandlerPrivate::HAdjustEditHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HAdjustEditHandler::HAdjustEditHandler(QObject *parent) :
    HAbstractGuiHandler(*new HAdjustEditHandlerPrivate, parent)
{
}

HAdjustEditHandler::~HAdjustEditHandler()
{
    qDebug() << __func__;
}

void HAdjustEditHandler::initialize(QVariantMap /*param*/)
{
}

QString HAdjustEditHandler::typeName()
{
    return "HAdjustEditHandler";
}

void HAdjustEditHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HAdjustEditHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)
    auto widget = new HAdjustDetailWidget();
    widget->setData(d->configManage->adjustCollection());
    HListCollectionDialog dlg;
    dlg.setWindowTitle(tr("调整数据配置"));
    dlg.setDataDetailWidget(widget);
    d->mainWindow->openCalibrateDlg(&dlg);
    d->model->addAction(ACT_RESET_ADJUST);
}

HE_GUI_END_NAMESPACE
