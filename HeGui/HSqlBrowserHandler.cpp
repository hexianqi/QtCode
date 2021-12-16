#include "HSqlBrowserHandler_p.h"
#include "HeCore/HAppContext.h"
#include "HeSql/ISqlBrowser.h"

HE_BEGIN_NAMESPACE

HSqlBrowserHandler::HSqlBrowserHandler(QObject *parent) :
    HAbstractGuiHandler(*new HSqlBrowserHandlerPrivate, parent)
{
}

HSqlBrowserHandler::~HSqlBrowserHandler() = default;

QString HSqlBrowserHandler::typeName()
{
    return "HSqlBrowserHandler";
}

void HSqlBrowserHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    auto browser = HAppContext::getContextPointer<ISqlBrowser>("ISqlBrowser");
    browser->revert();
    browser->show();
}

HE_END_NAMESPACE
