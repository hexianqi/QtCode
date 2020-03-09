#include "HProductInfoEditHandler_p.h"
#include "HeCore/HAppContext.h"
#include "HeSql/ISqlHandle.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HProductInfoEditHandlerPrivate::HProductInfoEditHandlerPrivate()
{
    handle = HAppContext::getContextPointer<ISqlHandle>("ISqlHandle");
}

HProductInfoEditHandler::HProductInfoEditHandler(QObject *parent) :
    HAbstractGuiHandler(*new HProductInfoEditHandlerPrivate, parent)
{
}

HProductInfoEditHandler::~HProductInfoEditHandler()
{
    qDebug() << __func__;
}

void HProductInfoEditHandler::initialize(QVariantMap /*param*/)
{
}

QString HProductInfoEditHandler::typeName()
{
    return "HProductInfoEditHandler";
}

void HProductInfoEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HProductInfoEditHandler);
    d->handle->editProductInfo();
}

HE_GUI_END_NAMESPACE
