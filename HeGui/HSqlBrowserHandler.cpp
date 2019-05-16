#include "HSqlBrowserHandler_p.h"
#include "HeCore/HAppContext.h"
#include "HeSql/ISqlBrowser.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSqlBrowserHandlerPrivate::HSqlBrowserHandlerPrivate()
{
    browser = HAppContext::getContextPointer<ISqlBrowser>("ISqlBrowser");
}

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

void HSqlBrowserHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HSqlBrowserHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)
    d->browser->show();
}

HE_GUI_END_NAMESPACE
