#include "HSpecTcHandler_p.h"
#include "IMainWindow.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include "HeData/IConfigManage.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/HSpecSetting.h"
#include <QtWidgets/QInputDialog>
#include <QtCore/QDebug>

HE_CORE_USE_NAMESPACE
HE_GUI_BEGIN_NAMESPACE

HSpecTcHandler::HSpecTcHandler(QObject *parent) :
    HAbstractConfigHandler(*new HSpecTcHandlerPrivate, parent)
{
}

HSpecTcHandler::~HSpecTcHandler()
{
    qDebug() << __func__;
}

QString HSpecTcHandler::typeName()
{
    return "HSpecTcHandler";
}

void HSpecTcHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HSpecTcHandler);
    bool ok;
    auto s = dynamic_cast<HSpecSetting *>(d->configManage->specCalibrate("1")->item(Setting));
    auto f = HCore::toFormatInfo("[标准色温]");
    auto v = QInputDialog::getDouble(d->mainWindow, tr("设置色温"), tr("设置色温："), s->data("[标准色温]").toDouble(), f->min(), f->max(), f->decimals(), &ok);
    if (ok)
        s->setData("[标准色温]", v);
}


HE_GUI_END_NAMESPACE
