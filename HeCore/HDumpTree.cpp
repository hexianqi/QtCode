#include "HDumpTree_p.h"
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QtDebug>

HE_BEGIN_NAMESPACE

void HDumpTreePrivate::dump(const QVariant &value, const QString &name, const QString &pointer, const QString &prefix)
{
    if (value.type() == QVariant::List)
    {
        qDebug() << QString("%1%2%3(%4)").arg(prefix, pointer, name, "QVariantList");
        return dump(value.toList(), pointer, prefix);
    }
    if (value.type() == QVariant::Map)
    {
        qDebug() << QString("%1%2%3(%4)").arg(prefix, pointer, name, "QVariantMap");
        return dump(value.toMap(), pointer, prefix);
    }
    if (value.canConvert<QVariantMap>())
    {
        qDebug() << QString("%1%2%3(%4)").arg(prefix, pointer, name, value.typeName());
        return dump(value.value<QAssociativeIterable>(), pointer, prefix);
    }
    if (value.canConvert<QVariantList>())
    {
        qDebug() << QString("%1%2%3(%4)").arg(prefix, pointer, name, value.typeName());
        return dump(value.value<QSequentialIterable>(), pointer, prefix);
    }
    auto text = name.isEmpty() ? value.toString() : name + " : " + value.toString();
    qDebug() << QString("%1%2%3(%4)").arg(prefix, pointer, text, value.typeName());
}

void HDumpTreePrivate::dump(const QVariantList &value, const QString &pointer, const QString &prefix)
{
    auto extension = pointer == tee ? branch : space;
    for (int i = 0; i < value.size(); i++)
        dump(value[i], "", i == value.size() - 1 ? last : tee, prefix + extension);
}

void HDumpTreePrivate::dump(const QVariantMap &value, const QString &pointer, const QString &prefix)
{
    auto extension = pointer == tee ? branch : space;
    for (auto it = value.begin(); it != value.end(); it++)
        dump(it.value(), it.key(), it == value.end() - 1 ? last : tee, prefix + extension);
}

void HDumpTreePrivate::dump(const QAssociativeIterable &value, const QString &pointer, const QString &prefix)
{
    auto extension = pointer == tee ? branch : space;
    for (auto it = value.begin(); it != value.end(); it++)
        dump(it.value(), it.key().toString(), it == value.end() - 1 ? last : tee, prefix + extension);
}

void HDumpTreePrivate::dump(const QSequentialIterable &value, const QString &pointer, const QString &prefix)
{
    auto extension = pointer == tee ? branch : space;
    for (int i = 0; i < value.size(); i++)
        dump(value.at(i), "", i == value.size() - 1 ? last : tee, prefix + extension);
}

void HDumpTreePrivate::dump(const QJsonValue &value, const QString &name, const QString &pointer, const QString &prefix)
{
    if (value.isArray())
    {
        qDebug() << QString("%1%2%3(%4)").arg(prefix, pointer, name, "QJsonArray");
        return dump(value.toArray(), pointer, prefix);
    }
    if (value.isObject())
    {
        qDebug() << QString("%1%2%3(%4)").arg(prefix, pointer, name, "QJsonObject");
        return dump(value.toObject(), pointer, prefix);
    }

    auto text = name.isEmpty() ? "" : name + " : ";
    if (value.isNull())
        qDebug() << QString("%1%2%3%4").arg(prefix, pointer, text, "null");
    if (value.isUndefined())
        qDebug() << QString("%1%2%3%4").arg(prefix, pointer, text, "undefined");
    if (value.isBool())
        qDebug() << QString("%1%2%3%5(%4)").arg(prefix, pointer, text, "bool").arg(value.toBool());
    if (value.isDouble())
        qDebug() << QString("%1%2%3%5(%4)").arg(prefix, pointer, text, "double").arg(value.toDouble());
    if (value.isString())
        qDebug() << QString("%1%2%3%5(%4)").arg(prefix, pointer, text, "string").arg(value.toString());
}

void HDumpTreePrivate::dump(const QJsonArray &value, const QString &pointer, const QString &prefix)
{
    auto extension = pointer == tee ? branch : space;
    for (int i = 0; i < value.size(); i++)
        dump(value[i], "", i == value.size() - 1 ? last : tee, prefix + extension);
}

void HDumpTreePrivate::dump(const QJsonObject &value, const QString &pointer, const QString &prefix)
{
    auto extension = pointer == tee ? branch : space;
    for (auto it = value.begin(); it != value.end(); it++)
        dump(it.value(), it.key(), it == value.end() - 1 ? last : tee, prefix + extension);
}

void HDumpTreePrivate::dump(const QObject *p, const QString &pointer, const QString &prefix)
{
    qDebug() << QString("%1%2%3 : %4").arg(prefix, pointer, p->metaObject()->className(), p->objectName());
    auto extension = pointer == tee ? branch : space;
    auto children = p->children();
    for (int i = 0; i < children.size(); i++)
        dump(children.at(i), i == children.size() - 1 ? last : tee, prefix + extension);
}

HDumpTree::HDumpTree(QObject *parent) :
    QObject(parent),
    d_ptr(new HDumpTreePrivate)
{
}

HDumpTree::~HDumpTree()
{
}

void HDumpTree::dump(const QVariant &value, const QString &name)
{
    HDumpTreePrivate d;
    d.dump(value, name, "");
}

void HDumpTree::dump(const QJsonValue &value, const QString &name)
{
    HDumpTreePrivate d;
    d.dump(value, name, "");
}

void HDumpTree::dump(const QObject *p)
{
    HDumpTreePrivate d;
    d.dump(p, "");
}

HE_END_NAMESPACE
