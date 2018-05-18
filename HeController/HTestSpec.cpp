#include "HTestSpec_p.h"
#include <QVector>

HE_CONTROLLER_BEGIN_NAMESPACE

HTestSpecPrivate::HTestSpecPrivate()
{
    addData("[积分时间]", 10);
}

HTestSpec::HTestSpec()
    : HTestData(*new HTestSpecPrivate)
{

}

HTestSpec::HTestSpec(HTestSpecPrivate &p)
    : HTestData(p)
{
}

HTestSpec::~HTestSpec()
{
}

void HTestSpec::initialize(QVariantMap param)
{
    HTestData::initialize(param);
}

bool HTestSpec::setSample(QVector<double> value, bool avg)
{
    return true;
}

void HTestSpec::clearQueue()
{

}

HE_CONTROLLER_END_NAMESPACE
