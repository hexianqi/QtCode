#include "HAbstractGuiHandler_p.h"
#include "HMainWindow.h"
#include "HeCore/HAppContext.h"
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractGuiHandlerPrivate::HAbstractGuiHandlerPrivate()
{
    parent = HAppContext::getContextPointer<QWidget>("MainWindow");
}

HAbstractGuiHandler::HAbstractGuiHandler(QObject *parent)
    : IGuiHandler(parent), d_ptr(new HAbstractGuiHandlerPrivate)
{
}

HAbstractGuiHandler::HAbstractGuiHandler(HAbstractGuiHandlerPrivate &p, QObject *parent)
    : IGuiHandler(parent), d_ptr(&p)
{
}

HAbstractGuiHandler::~HAbstractGuiHandler()
{
    qDebug() << __func__;
}

void HAbstractGuiHandler::initialize(QVariantMap param)
{
    if (param.contains("parent"))
        setParent(FromVariant(QObject, param.value("parent")));
}

HE_GUI_END_NAMESPACE
