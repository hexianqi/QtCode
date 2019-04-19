#include "HAbstractGuiHandler_p.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractGuiHandlerPrivate::HAbstractGuiHandlerPrivate()
{
    parent = HAppContext::getContextPointer<QWidget>("IMainWindow");
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

HE_GUI_END_NAMESPACE
