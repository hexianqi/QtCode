#include "HLocationEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HLocationEditWidget.h"
#include "HeData/IConfigManage.h"
#include "HeData/ILocationCollection.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HLocationEditHandler::HLocationEditHandler(QObject *parent) :
    HAbstractConfigHandler(*new HLocationEditHandlerPrivate, parent)
{
}

HLocationEditHandler::~HLocationEditHandler() = default;

QString HLocationEditHandler::typeName()
{
    return "HLocationEditHandler";
}

void HLocationEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HLocationEditHandler);
    HDataDetail<ILocation> detail;
    detail.setEditer(new HLocationEditWidget);
    detail.setData(d->configManage->locationCollection());
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("布局数据配置"));
    dlg.setDataDetail(&detail);
    dlg.resize(1000, 600);
    dlg.exec();
    d->model->addAction(ACT_RESET_LOCATION);
}

HE_END_NAMESPACE
