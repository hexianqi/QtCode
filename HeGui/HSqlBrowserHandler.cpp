#include "HSqlBrowserHandler_p.h"
#include "HeCore/HAppContext.h"
#include "HeSql/ISqlBrowser.h"

HE_BEGIN_NAMESPACE

HSqlBrowserHandler::HSqlBrowserHandler(QObject *parent) :
    HAbstractGuiHandler(*new HSqlBrowserHandlerPrivate, parent)
{
}

HSqlBrowserHandler::~HSqlBrowserHandler() = default;

void HSqlBrowserHandler::initialize(QVariantMap param)
{
    Q_D(HSqlBrowserHandler);
    if (param.contains("sqlBrowser"))
        d->sqlBrowser = param.value("sqlBrowser").toString();
}

QString HSqlBrowserHandler::typeName()
{
    return "HSqlBrowserHandler";
}

void HSqlBrowserHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HSqlBrowserHandler);
    if (d->sqlBrowser.isEmpty())
        d->sqlBrowser = "ISpecSqlBrowser";
    auto browser = HAppContext::getContextPointer<ISqlBrowser>(d->sqlBrowser);
    browser->revert();
    browser->showMaximized();
}

HE_END_NAMESPACE
