#include "HModel2000_p.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IPort.h"
#include "HeCommunicate/IDevice.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeCommunicate/IProtocolCollection.h"
#include "HeCommunicate/ICommunicateFactory.h"
#include "HeController/HThreadSpec.h"

HModel2000Private::HModel2000Private(HModel2000 *q)
    : HAbstractModelPrivate(q)
{
}


HModel2000::HModel2000(QObject *parent)
    : HAbstractModel(*new HModel2000Private(this), parent)
{
}

HModel2000::HModel2000(HModel2000Private &p, QObject *parent)
    : HAbstractModel(p, parent)
{
}

HModel2000::~HModel2000()
{
}

QString HModel2000::typeName()
{
    return "HModel2000";
}
