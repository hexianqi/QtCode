#include "HAppContext.h"

HE_BEGIN_NAMESPACE

QHash<QString, QVariant> HAppContext::__contextValue;
QHash<QString, void *> HAppContext::__contextPointer;

void HAppContext::setContextValue(const QString &key, const QVariant &value)
{
    __contextValue[key] = value;
}

QVariant HAppContext::getContextValue(const QString &key)
{
    if (!__contextValue.contains(key))
        return QVariant();
    return __contextValue.value(key);
}

void HAppContext::setContextPointer(const QString &key, void *value)
{
    __contextPointer[key] = value;
}

void *HAppContext::getContextPointer(const QString &key)
{
    if (!__contextPointer.contains(key))
        return nullptr;
    return __contextPointer.value(key);
}

HE_END_NAMESPACE
