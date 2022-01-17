#pragma once

#include "HDumpTree.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HDumpTreePrivate
{
public:
    void dump(const QVariant &value, const QString &name, const QString &pointer, const QString &prefix = QString());
    void dump(const QVariantList &value, const QString &pointer, const QString &prefix = QString());
    void dump(const QVariantMap &value, const QString &pointer, const QString &prefix = QString());
    void dump(const QAssociativeIterable &value, const QString &pointer, const QString &prefix = QString());
    void dump(const QSequentialIterable &value, const QString &pointer, const QString &prefix = QString());
    void dump(const QJsonValue &value, const QString &name, const QString &pointer, const QString &prefix = QString());
    void dump(const QJsonArray &value, const QString &pointer, const QString &prefix = QString());
    void dump(const QJsonObject &value, const QString &pointer, const QString &prefix = QString());
    void dumpChild(const QObject *, const QString &pointer, const QString &prefix = QString());
    void dumpProperty(const QObject *, const QString &pointer, const QString &prefix = QString());

protected:
    QString space  = "    ";
    QString branch = "│  ";
    QString tee    = "├─";
    QString last   = "└─";
};

HE_END_NAMESPACE

