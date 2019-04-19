#include "HAction_p.h"
#include "HeCore/IHandler.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAction::HAction(QObject* parent)
    : QAction(parent), d_ptr(new HActionPrivate)
{
    connect(this, &HAction::triggered, this, call);
}

HAction::HAction(HActionPrivate &p, QObject *parent)
    : QAction(parent), d_ptr(&p)
{
}

HAction::~HAction()
{
    qDebug() << __func__;
}

void HAction::initialize(QVariantMap param)
{
    if (param.contains("handler"))
        d_ptr->handler = FromVariant(IHandler, param.value("handler"));
    if (param.contains("data"))
        setData(param.value("data"));
}

QString HAction::typeName()
{
    return "HAction";
}

void HAction::setHandler(IHandler *p)
{
    d_ptr->handler = p;
}

void HAction::call()
{
    Q_ASSERT_X(d_ptr->handler != nullptr, "HAction", " The handler is not init.");
    QVariantMap param;
    param.insert("data", this->data());
    d_ptr->handler->execute(this, param);
}

HE_GUI_END_NAMESPACE
