#include "HDoublePropertyManager_p.h"

HDoublePropertyManager::HDoublePropertyManager(QObject *parent) :
    QtDoublePropertyManager(parent),
    d_ptr(new HDoublePropertyManagerPrivate)
{
}

HDoublePropertyManager::HDoublePropertyManager(HDoublePropertyManagerPrivate &p, QObject *parent) :
    QtDoublePropertyManager(parent),
    d_ptr(&p)
{
}

HDoublePropertyManager::~HDoublePropertyManager() = default;

QString HDoublePropertyManager::prefix(const QtProperty *property) const
{
    return d_ptr->propertyToData.contains(property) ? d_ptr->propertyToData[property].prefix : QString();
}

QString HDoublePropertyManager::suffix(const QtProperty *property) const
{
    return d_ptr->propertyToData.contains(property) ? d_ptr->propertyToData[property].suffix : QString();
}

void HDoublePropertyManager::setPrefix(QtProperty *property, const QString &prefix)
{
    if (!d_ptr->propertyToData.contains(property))
        return;

    auto data = d_ptr->propertyToData[property];
    if (data.prefix == prefix)
        return;

    data.prefix = prefix;
    d_ptr->propertyToData[property] = data;

    emit propertyChanged(property);
    emit prefixChanged(property, prefix);
}

void HDoublePropertyManager::setSuffix(QtProperty *property, const QString &suffix)
{
    if (!d_ptr->propertyToData.contains(property))
        return;

    auto data = d_ptr->propertyToData[property];
    if (data.suffix == suffix)
        return;

    data.suffix = suffix;
    d_ptr->propertyToData[property] = data;

    emit propertyChanged(property);
    emit suffixChanged(property, suffix);
}

QString HDoublePropertyManager::valueText(const QtProperty *property) const
{
    auto text = QtDoublePropertyManager::valueText(property);
    if (!d_ptr->propertyToData.contains(property))
        return text;

    auto data = d_ptr->propertyToData[property];
    text = data.prefix + text + data.suffix;

    return text;
}

void HDoublePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->propertyToData[property] = HDoublePropertyManagerPrivate::Data();
    QtDoublePropertyManager::initializeProperty(property);
}

void HDoublePropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->propertyToData.remove(property);
    QtDoublePropertyManager::uninitializeProperty(property);
}

