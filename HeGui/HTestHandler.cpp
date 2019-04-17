#include "HTestHandler_p.h"
#include <QtWidgets/QMessageBox>

HE_GUI_BEGIN_NAMESPACE

HTestHandler::HTestHandler(QObject *parent) :
    HAbstractGuiHandler(*new HTestHandlerPrivate, parent)
{
}

HTestHandler::~HTestHandler()
{
}

QString HTestHandler::typeName()
{
    return "HTestHandler";
}

void HTestHandler::execute(QObject *sender, QVariantMap param)
{
    Q_UNUSED(sender)
    Q_UNUSED(param)
    Q_D(HTestHandler);
    QMessageBox::information(d->parent, "" , tr("敬请期待"));
}

HE_GUI_END_NAMESPACE
