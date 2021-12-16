#include "HAction_p.h"
#include "HeCore/HDefine.h"
#include "HeCore/IHandler.h"

HE_BEGIN_NAMESPACE

HAction::HAction(QObject* parent) :
    QAction(parent),
    d_ptr(new HActionPrivate)
{
}

HAction::~HAction() = default;

HAction::HAction(HActionPrivate &p, QObject *parent) :
    QAction(parent),
    d_ptr(&p)
{
}

void HAction::initialize(QVariantMap param)
{
    if (param.contains("handler"))
        setHandler(FromVariant(IHandler, param.value("handler")));
    if (param.contains("data"))
        setData(param.value("data"));
    if (param.contains("property"))
    {
        auto value = param.value("property").toMap();
        for (auto i = value.begin(); i != value.end(); i++)
            setProperty(i.key().toUtf8().constData(), i.value());
    }
}

QString HAction::typeName()
{
    return "HAction";
}

void HAction::setHandler(IHandler *p)
{
    d_ptr->handler = p;
    connect(this, &HAction::triggered, this, &HAction::call);
}

void HAction::call()
{
    Q_ASSERT_X(d_ptr->handler != nullptr, "HAction", " The handler is not init.");
    QVariantMap param;
    param.insert("data", this->data());
    d_ptr->handler->execute(this, param);
}

HE_END_NAMESPACE
