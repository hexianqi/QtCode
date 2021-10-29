#include "HProductEditHandler_p.h"
#include "HProductEditDialog.h"
#include "HeCore/HAppContext.h"
//#include "HeSql/ISqlHandle.h"
#include <QtCore/QDebug>

//HE_SQL_USE_NAMESPACE
HE_GUI_BEGIN_NAMESPACE

HProductEditHandler::HProductEditHandler(QObject *parent) :
    HAbstractGuiHandler(*new HProductEditHandlerPrivate, parent)
{
}

HProductEditHandler::~HProductEditHandler()
{
    qDebug() << __func__;
}

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

HE_GUI_END_NAMESPACE
