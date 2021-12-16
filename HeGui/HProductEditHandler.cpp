#include "HProductEditHandler_p.h"
#include "HProductEditDialog.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HProductEditHandler::HProductEditHandler(QObject *parent) :
    HAbstractGuiHandler(*new HProductEditHandlerPrivate, parent)
{
}

HProductEditHandler::~HProductEditHandler() = default;

QString HProductEditHandler::typeName()
{
    return "HProductEditHandler";
}

void HProductEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    HProductEditDialog dlg;
    dlg.exec();
//    HAppContext::getContextPointer<ISqlHandle>("ISqlHandle")->editProductInfo();
}

HE_END_NAMESPACE
