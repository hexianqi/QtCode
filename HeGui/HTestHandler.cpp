#include "HTestHandler.h"
#include "HAbstractGuiHandler_p.h"
#include <QMessageBox>

HE_GUI_BEGIN_NAMESPACE

HTestHandler::HTestHandler(QObject *parent)
    : HAbstractGuiHandler(parent)
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
    QMessageBox::information(d_ptr->parent, "" , tr("敬请期待"));
}

HE_GUI_END_NAMESPACE
