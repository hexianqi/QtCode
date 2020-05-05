#include "HSqlBrowserHandler_p.h"
#include "HeCore/HAppContext.h"
#include "HeSql/ISqlBrowser.h"
#include <QtCore/QDebug>

HE_SQL_USE_NAMESPACE
HE_GUI_BEGIN_NAMESPACE

HSqlBrowserHandler::HSqlBrowserHandler(QObject *parent) :
    HAbstractGuiHandler(*new HSqlBrowserHandlerPrivate, parent)
{
}

HSqlBrowserHandler::~HSqlBrowserHandler()
{
    qDebug() << __func__;
}

void HSqlBrowserHandler::initialize(QVariantMap /*param*/)
{
}

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

HE_GUI_END_NAMESPACE
