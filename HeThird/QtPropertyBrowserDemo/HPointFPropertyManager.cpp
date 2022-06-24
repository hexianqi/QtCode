#include "HPointFPropertyManager_p.h"

HPointFPropertyManager::HPointFPropertyManager(QObject *parent) :
    QtVariantPropertyManager(parent),
    d_ptr(new HPointFPropertyManagerPrivate)
{
    init();
}

HPointFPropertyManager::HPointFPropertyManager(HPointFPropertyManagerPrivate &p, QObject *parent) :
    QtVariantPropertyManager(parent),
    d_ptr(&p)
{
    init();
}

HPointFPropertyManager::~HPointFPropertyManager() = default;

bool HPointFPropertyManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == QVariant::PointF)
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int HPointFPropertyManager::valueType(int propertyType) const
{
    if (propertyType == QVariant::PointF)
        return QVariant::PointF;
    return QtVariantPropertyManager::valueType(propertyType);
}

QVariant HPointFPropertyManager::value(const QtProperty *property) const
{
    if (d_ptr->propertyToData.contains(property))
        return d_ptr->propertyToData[property].value;
    return QtVariantPropertyManager::value(property);
}

QString HPointFPropertyManager::valueText(const QtProperty *property) const
{
    if (d_ptr->propertyToData.contains(property))
    {
        auto point = d_ptr->propertyToData[property].value.toPointF();
        return QString("(%1, %2)").arg(point.x()).arg(point.y());
    }
    return QtVariantPropertyManager::valueText(property);
}

void HPointFPropertyManager::setValue(QtProperty *property, const QVariant &value)
{
    if (d_ptr->propertyToData.contains(property))
    {
        if (value.type() != QVariant::PointF && !value.canConvert(QVariant::PointF))
            return;
        auto point = value.toPointF();
        auto data = d_ptr->propertyToData[property];
        data.value = point;
        if (data.x)
            data.x->setValue(point.x());
        if (data.y)
            data.y->setValue(point.y());
        d_ptr->propertyToData[property] = data;
        emit propertyChanged(property);
        emit valueChanged(property, point);
        return;
    }
    QtVariantPropertyManager::setValue(property, value);
}

void HPointFPropertyManager::initializeProperty(QtProperty *property)
{
    if (propertyType(property) == QVariant::PointF)
    {
        HPointFPropertyManagerPrivate::Data data;
        data.value = QPointF(0, 0);
        data.x = addProperty(QVariant::Double);
        data.x->setPropertyName("Position X");
        data.y = addProperty(QVariant::Double);
        data.y->setPropertyName("Position Y");
        property->addSubProperty(data.x);
        property->addSubProperty(data.y);
        d_ptr->propertyToData[property] = data;
        d_ptr->xToProperty[data.x] = property;
        d_ptr->yToProperty[data.y] = property;
    }
    QtVariantPropertyManager::initializeProperty(property);
}

void HPointFPropertyManager::uninitializeProperty(QtProperty *property)
{
    if (d_ptr->propertyToData.contains(property))
    {
        auto data = d_ptr->propertyToData[property];
        if (data.x)
            d_ptr->xToProperty.remove(data.x);
        if (data.y)
            d_ptr->yToProperty.remove(data.y);
        d_ptr->propertyToData.remove(property);
    }
    QtVariantPropertyManager::uninitializeProperty(property);
}

void HPointFPropertyManager::init()
{
//  析构时候有问题
//  connect(this, &HPointFPropertyManager::valueChanged, this, &HPointFPropertyManager::slotValueChanged);
//  connect(this, &HPointFPropertyManager::propertyDestroyed, this, &HPointFPropertyManager::slotPropertyDestroyed);
    connect(this, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));
    connect(this, SIGNAL(propertyDestroyed(QtProperty *)), this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

void HPointFPropertyManager::slotValueChanged(QtProperty *property, const QVariant &value)
{
    if (d_ptr->xToProperty.contains(property))
    {
        auto pointProperty = d_ptr->xToProperty[property];
        auto point = this->value(pointProperty).toPointF();
        point.setX(value.toDouble());
        setValue(pointProperty, point);
    }
    else if (d_ptr->yToProperty.contains(property))
    {
        auto pointProperty = d_ptr->yToProperty[property];
        auto point = this->value(pointProperty).toPointF();
        point.setY(value.toDouble());
        setValue(pointProperty, point);
    }
}

void HPointFPropertyManager::slotPropertyDestroyed(QtProperty *property)
{
    if (d_ptr->xToProperty.contains(property))
    {
        auto pointProperty = d_ptr->xToProperty[property];
        d_ptr->propertyToData[pointProperty].x = 0;
        d_ptr->xToProperty.remove(property);
    }
    else if (d_ptr->yToProperty.contains(property))
    {
        auto pointProperty = d_ptr->yToProperty[property];
        d_ptr->propertyToData[pointProperty].y = 0;
        d_ptr->yToProperty.remove(property);
    }
}




