#include "HAppContext.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QString, QVariant> HAppContext::__contextValue;
QHash<QString, void *> HAppContext::__contextPointer;

void HAppContext::setContextValue(QString key, QVariant value)
{
    __contextValue[key] = value;
}

void HAppContext::setContextPointer(QString key, void *value)
{
    __contextPointer[key] = value;
}

QVariant HAppContext::getContextValue(QString key)
{
    if (!__contextValue.contains(key))
        return QVariant();
    return __contextValue.value(key);
}

void *HAppContext::getContextPointer(QString key)
{
    if (!__contextPointer.contains(key))
        return nullptr;
    return __contextPointer.value(key);
}

HE_CORE_END_NAMESPACE
