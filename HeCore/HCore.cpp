#include "HCore.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

HE_BEGIN_NAMESPACE

QString HCore::toJson(QVariantMap value)
{
    auto obj = QJsonObject::fromVariantMap(value);
    auto doc = QJsonDocument(obj);
    return doc.toJson(QJsonDocument::Compact);
}

QVariantMap HCore::fromJson(QString value)
{
    auto doc = QJsonDocument::fromJson(value.toUtf8());
    if (doc.isObject())
        return doc.object().toVariantMap();
    return {};
}

QString HCore::typeAddition(const QString &type, const QString &addition)
{
    return  QString("%1_%2]").arg(type.left(type.size() - 1), addition);
}

HE_END_NAMESPACE
