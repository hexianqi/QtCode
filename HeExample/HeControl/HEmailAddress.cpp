#include "HEmailAddress_p.h"

HE_BEGIN_NAMESPACE

HEmailAddress::HEmailAddress(QObject *parent) :
    QObject(parent),
    d_ptr(new HEmailAddressPrivate)
{
}

HEmailAddress::HEmailAddress(const QString &address, const QString &name, QObject *parent) :
    QObject(parent),
    d_ptr(new HEmailAddressPrivate)
{
    setAddress(address);
    setName(name);
}

HEmailAddress::~HEmailAddress() = default;

HEmailAddress *HEmailAddress::fromString(const QString &value, QObject *parent)
{
    auto p1 = value.indexOf("<");
    auto p2 = value.indexOf(">");
    if (p1 == -1)
        return new HEmailAddress(value, "", parent);
    return new HEmailAddress(value.mid(p1 + 1, p2 - p1 - 1), value.left(p1), parent);
}

QString HEmailAddress::name() const
{
    return d_ptr->name;
}

QString HEmailAddress::address() const
{
    return  d_ptr->address;
}

void HEmailAddress::setName(const QString &value)
{
    if (d_ptr->name == value)
        return;
    d_ptr->name = value;
}

void HEmailAddress::setAddress(const QString &value)
{
    if (d_ptr->address == value)
        return;
    d_ptr->address = value;
}

HE_END_NAMESPACE
