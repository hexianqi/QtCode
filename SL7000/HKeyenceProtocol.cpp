#include "HKeyenceProtocol_p.h"
#include "HeCommunicate/IDevice.h"

HKeyenceProtocolPrivate::HKeyenceProtocolPrivate()
{

}

HKeyenceProtocol::HKeyenceProtocol() :
    HBigProtocol(*new HKeyenceProtocolPrivate)
{
}

HKeyenceProtocol::HKeyenceProtocol(HKeyenceProtocolPrivate &p) :
    HBigProtocol(p)
{
}

HKeyenceProtocol::~HKeyenceProtocol() = default;

void HKeyenceProtocol::initialize(QVariantMap param)
{
    Q_D(HKeyenceProtocol);
    d->device->initialize(param);
}

QString HKeyenceProtocol::typeName()
{
    return "HKeyenceProtocol";
}
