#include "HProtocolInfo_p.h"
#include "HAbstractPort.h"

HE_COMMUNICATE_USE_NAMESPACE

HProtocolInfo::HProtocolInfo()
    : d_ptr(new HProtocolInfoPrivate)
{
}

HProtocolInfo::HProtocolInfo(const HProtocolInfo &rhs)
    : d_ptr(rhs.d_ptr)
{
}

HProtocolInfo::HProtocolInfo(HProtocolInfoPrivate &p)
    : d_ptr(&p)
{
}

HProtocolInfo &HProtocolInfo::operator=(const HProtocolInfo &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

HProtocolInfo::~HProtocolInfo()
{
}

void HProtocolInfo::initialize(QVariantMap param)
{
    if (param.contains("port"))
        d_ptr->port = static_cast<IPort *>(param.value("port").value<void *>());
    if (param.contains("portNum"))
        d_ptr->portNum = param.value("portNum").toInt();
    if (param.contains("portNumScan"))
        d_ptr->portNumScan = param.value("portNumScan").toBool();
    if (param.contains("deviceID"))
        d_ptr->deviceID = param.value("deviceID").toInt();
}

void HProtocolInfo::setPort(IPort *port, int num, bool scan)
{
    d_ptr->port = port;
    d_ptr->portNum = num;
    d_ptr->portNumScan = scan;
}

void HProtocolInfo::setPortNum(int num)
{
    d_ptr->portNum = num;
}

void HProtocolInfo::setDeviceID(int id)
{
    d_ptr->deviceID = id;
}

void HProtocolInfo::addActionParam(HActionType key, QList<uchar> value)
{
    d_ptr->actionParam.insert(key, value);
}

IPort * HProtocolInfo::port()
{
    return d_ptr->port;
}

int HProtocolInfo::portNum()
{
    return d_ptr->portNum;
}

bool HProtocolInfo::isPortNumScan()
{
    return d_ptr->portNumScan;
}

int HProtocolInfo::deviceID()
{
    return d_ptr->deviceID;
}

QList<uchar> HProtocolInfo::actionParam(HActionType key)
{
    return d_ptr->actionParam.value(key);
}
