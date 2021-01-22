#include "HDaXinProtocol_p.h"
#include "HDaXinDevice.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HDaXinProtocolPrivate::HDaXinProtocolPrivate()
{
    device = new HDaXinDevice;
}

HDaXinProtocol::HDaXinProtocol() :
    HBigProtocol(*new HDaXinProtocolPrivate)
{
}

HDaXinProtocol::HDaXinProtocol(HDaXinProtocolPrivate &p) :
    HBigProtocol(p)
{
}

HDaXinProtocol::~HDaXinProtocol()
{
    qDebug() << __func__;
}

void HDaXinProtocol::initialize(QVariantMap param)
{
    Q_D(HDaXinProtocol);
    d->device->initialize(param);
}

QString HDaXinProtocol::typeName()
{
    return "HDaXinProtocol";
}

HE_COMMUNICATE_END_NAMESPACE
