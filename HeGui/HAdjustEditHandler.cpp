#include "HAdjustEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HAdjustEditWidget.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjustCollection.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HAdjustEditHandler::HAdjustEditHandler(QObject *parent) :
    HAbstractConfigHandler(*new HAdjustEditHandlerPrivate, parent)
{
}

HAdjustEditHandler::~HAdjustEditHandler() = default;

QString HAdjustEditHandler::typeName()
{
    return "HAdjustEditHandler";
}

void HAdjustEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAdjustEditHandler);
    HDataDetail<IAdjust> detail;
    detail.setEditer(new HAdjustEditWidget);
    detail.setData(d->configManage->adjustCollection());
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("调整数据配置"));
    dlg.setDataDetail(&detail);
    dlg.setMinimumSize(1115, 600);
    d->mainWindow->openDialog(&dlg);
    d->model->addAction(ACT_RESET_ADJUST);
}

HE_END_NAMESPACE
