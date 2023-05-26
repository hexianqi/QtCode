#include "HProtocol_p.h"

HE_BEGIN_NAMESPACE

HProtocol::HProtocol(QObject *parent) :
    HAbstractProtocol(*new HProtocolPrivate, parent)
{
}

HProtocol::HProtocol(HProtocolPrivate &p, QObject *parent) :
    HAbstractProtocol(p, parent)
{
}

HProtocol::~HProtocol()
{
}

QString HProtocol::typeName()
{
    return "HProtocol";
}

HE_END_NAMESPACE
