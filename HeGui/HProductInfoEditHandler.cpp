#include "HProductInfoEditHandler_p.h"
#include "HeCore/HAppContext.h"
#include "HeSql/ISqlHandle.h"
#include <QtCore/QDebug>

HE_SQL_USE_NAMESPACE
HE_GUI_BEGIN_NAMESPACE

HProductInfoEditHandler::HProductInfoEditHandler(QObject *parent) :
    HAbstractGuiHandler(*new HProductInfoEditHandlerPrivate, parent)
{
}

HProductInfoEditHandler::~HProductInfoEditHandler()
{
    qDebug() << __func__;
}

QString HProductInfoEditHandler::typeName()
{
    return "HProductInfoEditHandler";
}

void HProductInfoEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    HAppContext::getContextPointer<ISqlHandle>("ISqlHandle")->editProductInfo();
}

HE_GUI_END_NAMESPACE
