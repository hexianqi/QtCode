#include "HPrintSettingHandler_p.h"
#include "IGuiFactory.h"
#include "IMainWindow.h"
#include "IPrintSettingDialog.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HPrintSettingHandlerPrivate::HPrintSettingHandlerPrivate()
{
    guiFactory = HAppContext::getContextPointer<IGuiFactory>("IGuiFactory");
}

HPrintSettingHandler::HPrintSettingHandler(QObject *parent) :
    HAbstractGuiHandler(*new HPrintSettingHandlerPrivate, parent)
{
}

HPrintSettingHandler::~HPrintSettingHandler() = default;

void HPrintSettingHandler::initialize(QVariantMap param)
{
    Q_D(HPrintSettingHandler);
    if (param.contains("printTemplate"))
        d->printTemplate = param.value("printTemplate").toString();
    if (param.contains("printSettingDialog"))
        d->printSettingDialog = param.value("printSettingDialog").toString();
}

QString HPrintSettingHandler::typeName()
{
    return "HPrintSettingHandler";
}

void HPrintSettingHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HPrintSettingHandler);

    auto temp = HAppContext::getContextPointer<IPrintTemplate>(d->printTemplate);
    auto dialog = d->guiFactory->createPrintSettingDialog(d->printSettingDialog, d->mainWindow);
    if (dialog == nullptr || temp == nullptr)
        return;
    dialog->setPrintTemplate(temp);
    dialog->exec();
}



HE_END_NAMESPACE
