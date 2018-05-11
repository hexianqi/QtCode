#include "HAction_p.h"
#include "HeCore/IHandler.h"

HE_GUI_USE_NAMESPACE

HAction::HAction(QObject* parent)
    : QAction(parent), d_ptr(new HActionPrivate)
{
    connect(this, &HAction::triggered, this, &HAction::call);
}

HAction::HAction(HActionPrivate &p, QObject *parent)
    : QAction(parent), d_ptr(&p)
{
}

HAction::~HAction()
{

}

void HAction::initialize(QVariantMap param)
{
    if (param.contains("handler"))
        d_ptr->handler = FromVariant(IHandler, param.value("handler"));
    if (param.contains("data"))
        setData(param.value("data"));
}

void HAction::setHandler(IHandler *handler)
{
    d_ptr->handler = handler;
}

void HAction::call()
{
    if (d_ptr->handler == nullptr)
        throw std::logic_error(QString("Action'%1': The handler is not init.").arg(text()).toStdString());
    QVariantMap param;
    param.insert("data", this->data());
    d_ptr->handler->execute(this, param);
}
