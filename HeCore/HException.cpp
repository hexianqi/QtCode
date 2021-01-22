#include "HException.h"
#include "HCore.h"

HE_CORE_BEGIN_NAMESPACE

HException::HException(HErrorType value)
{
    _type = value;
}

HException::HException(QString value)
{
    _message = value;
}

void HException::raise() const
{
    throw *this;
}

HException *HException::clone() const
{
    return new HException(*this);
}

QString HException::message()
{
    return _message.isEmpty() ? HCore::toComment(_type) : _message;
}

HE_CORE_END_NAMESPACE
