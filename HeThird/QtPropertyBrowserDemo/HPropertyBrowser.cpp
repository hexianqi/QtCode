#include "HPropertyBrowser_p.h"
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include <QtCore/QMetaProperty>
#include <QtWidgets/QVBoxLayout>

bool isSubValue(int value, int subValue)
{
    if (value == subValue)
        return true;

    int i = 0;
    while (subValue)
    {
        if (!(value & (1 << i)))
        {
            if (subValue & 1)
                return false;
        }
        i++;
        subValue = subValue >> 1;
    }
    return true;
}

bool isPowerOf2(int value)
{
    while (value)
    {
        if (value & 1)
            return value == 1;
        value = value >> 1;
    }
    return false;
}

int flagToInt(const QMetaEnum &metaEnum, int flagValue)
{
    if (!flagValue)
        return 0;
    int intValue = 0;
    QMap<int, int> values; // dont show multiple enum values which have the same values
    int pos = 0;
    for (int i = 0; i < metaEnum.keyCount(); i++)
    {
        int value = metaEnum.value(i);
        if (!values.contains(value) && isPowerOf2(value))
        {
            if (isSubValue(flagValue, value))
                intValue |= (1 << pos);
            values[value] = pos++;
        }
    }
    return intValue;
}

int intToFlag(const QMetaEnum &metaEnum, int intValue)
{
    QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
    QList<int> values;
    for (int i = 0; i < metaEnum.keyCount(); i++)
    {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value) && isPowerOf2(value))
        {
            valueMap[value] = true;
            values.append(value);
        }
    }
    int flagValue = 0;
    int temp = intValue;
    int i = 0;
    while (temp)
    {
        if (i >= values.count())
            return -1;
        if (temp & 1)
            flagValue |= values.at(i);
        i++;
        temp = temp >> 1;
    }
    return flagValue;
}

int enumToInt(const QMetaEnum &metaEnum, int enumValue)
{
    QMap<int, int> values; // dont show multiple enum values which have the same values
    int pos = 0;
    for (int i = 0; i < metaEnum.keyCount(); i++)
    {
        int value = metaEnum.value(i);
        if (!values.contains(value))
        {
            if (value == enumValue)
                return pos;
            values[value] = pos++;
        }
    }
    return -1;
}

int intToEnum(const QMetaEnum &metaEnum, int intValue)
{
    QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
    QList<int> values;
    for (int i = 0; i < metaEnum.keyCount(); i++)
    {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value))
        {
            valueMap[value] = true;
            values.append(value);
        }
    }
    return intValue >= values.count() ? -1 : values.at(intValue);
}

void HPropertyBrowserPrivate::addClassProperties(const QMetaObject *metaObject)
{
    if (metaObject == nullptr)
        return;

    if (showParent)
        addClassProperties(metaObject->superClass());

    auto classProperty = classToProperty.value(metaObject);
    if (classProperty == nullptr)
    {
        classProperty = manager->addProperty(QtVariantPropertyManager::groupTypeId(), metaObject->className());
        classToProperty[metaObject] = classProperty;
        propertyToClass[classProperty] = metaObject;
        for (int index = metaObject->propertyOffset(); index < metaObject->propertyCount(); index++)
        {
            auto metaProperty = metaObject->property(index);
            auto name = QString(metaProperty.name());
            auto type = metaProperty.userType();
            QtVariantProperty *subProperty = nullptr;
            if (!metaProperty.isReadable())
            {
                subProperty = readOnlyManager->addProperty(QVariant::String, name);
                subProperty->setValue("< Non Readable >");
            }
            else if (metaProperty.isEnumType())
            {
                QMap<int, bool> values;
                QStringList names;
                auto metaEnum = metaProperty.enumerator();
                for (int i = 0; i < metaEnum.keyCount(); i++)
                {
                    auto value = metaEnum.value(i);
                    if (!values.contains(value))
                    {
                        if (!metaProperty.isFlagType() || isPowerOf2(value))
                        {
                            values[value] = true;
                            names.append(metaEnum.key(i));
                        }
                    }
                }
                if (metaProperty.isFlagType())
                {
                    subProperty = manager->addProperty(QtVariantPropertyManager::flagTypeId(), name);
                    subProperty->setAttribute("flagNames", names);
                    subProperty->setValue(flagToInt(metaEnum, metaProperty.read(object).toInt()));
                }
                else
                {
                    subProperty = manager->addProperty(QtVariantPropertyManager::enumTypeId(), name);
                    subProperty->setAttribute("enumNames", names);
                    subProperty->setValue(enumToInt(metaEnum, metaProperty.read(object).toInt()));
                }
            }
            else if (manager->isPropertyTypeSupported(type))
            {
                if (!metaProperty.isWritable())
                    subProperty = readOnlyManager->addProperty(type, name + " (Non Writable)");
                if (!metaProperty.isDesignable())
                    subProperty = readOnlyManager->addProperty(type, name + " (Non Designable)");
                else
                    subProperty = manager->addProperty(type, name);
                subProperty->setValue(metaProperty.read(object));
            }
            else
            {
                subProperty = readOnlyManager->addProperty(QVariant::String, name);
                subProperty->setValue("< Unknown Type >");
                subProperty->setEnabled(false);
            }
            classProperty->addSubProperty(subProperty);
            propertyToIndex[subProperty] = index;
            classToIndexToProperty[metaObject][index] = subProperty;
        }
    }
    else
        updateClassProperties(metaObject, false);

    topLevelProperties.append(classProperty);
    browser->addProperty(classProperty);
}

void HPropertyBrowserPrivate::updateClassProperties(const QMetaObject *metaObject, bool recursive)
{
    if (metaObject == nullptr)
        return;

    if (showParent && recursive)
        updateClassProperties(metaObject->superClass(), recursive);

    auto classProperty = classToProperty.value(metaObject);
    if (classProperty == nullptr)
        return;

    for (int index = metaObject->propertyOffset(); index < metaObject->propertyCount(); index++)
    {
        auto metaProperty = metaObject->property(index);
        if (metaProperty.isReadable() && classToIndexToProperty.contains(metaObject) && classToIndexToProperty[metaObject].contains(index))
        {
            auto subProperty = classToIndexToProperty[metaObject][index];
            if (metaProperty.isEnumType())
            {
                if (metaProperty.isFlagType())
                    subProperty->setValue(flagToInt(metaProperty.enumerator(), metaProperty.read(object).toInt()));
                else
                    subProperty->setValue(enumToInt(metaProperty.enumerator(), metaProperty.read(object).toInt()));
            }
            else
                subProperty->setValue(metaProperty.read(object));
        }
    }
}

HPropertyBrowser::HPropertyBrowser(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HPropertyBrowserPrivate)
{
    init();
}

HPropertyBrowser::HPropertyBrowser(HPropertyBrowserPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HPropertyBrowser::~HPropertyBrowser() = default;

QObject *HPropertyBrowser::object() const
{
    return d_ptr->object;
}

bool HPropertyBrowser::isShowParent() const
{
    return d_ptr->showParent;
}

void HPropertyBrowser::setObject(QObject *p)
{
    if (d_ptr->object == p)
        return;

    clear();
    d_ptr->object = p;
    build();
}

void HPropertyBrowser::setShowParent(bool b)
{
    if (d_ptr->showParent == b)
        return;
    d_ptr->showParent = b;
    clear();
    build();
}

void HPropertyBrowser::init()
{
    d_ptr->factory = new QtVariantEditorFactory(this);
    d_ptr->manager = new QtVariantPropertyManager(this);
    d_ptr->readOnlyManager = new QtVariantPropertyManager(this);
    d_ptr->browser = new QtTreePropertyBrowser(this);
    d_ptr->browser->setRootIsDecorated(false);
    d_ptr->browser->setFactoryForManager(d_ptr->manager, d_ptr->factory);
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(d_ptr->browser);
    connect(d_ptr->manager, &QtVariantPropertyManager::valueChanged, this, &HPropertyBrowser::handleValueChanged);
}

void HPropertyBrowser::clear()
{
    if (d_ptr->object == nullptr)
        return;
    for (auto it : d_ptr->topLevelProperties)
        d_ptr->browser->removeProperty(it);
    d_ptr->topLevelProperties.clear();
}

void HPropertyBrowser::build()
{
    if (!d_ptr->object)
        return;
    d_ptr->addClassProperties(d_ptr->object->metaObject());
}

void HPropertyBrowser::handleValueChanged(QtProperty *property, const QVariant &value)
{
    if (!d_ptr->propertyToIndex.contains(property))
        return;

    auto index = d_ptr->propertyToIndex.value(property);
    auto metaObject = d_ptr->object->metaObject();
    auto metaProperty = metaObject->property(index);
    if (metaProperty.isEnumType())
    {
        if (metaProperty.isFlagType())
            metaProperty.write(d_ptr->object, intToFlag(metaProperty.enumerator(), value.toInt()));
        else
            metaProperty.write(d_ptr->object, intToEnum(metaProperty.enumerator(), value.toInt()));
    }
    else
        metaProperty.write(d_ptr->object, value);
    d_ptr->updateClassProperties(metaObject, true);
}
