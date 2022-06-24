/***************************************************************************************************
**      2021-12-23  HDictionary 可以按"."来访问的字典类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HDictionaryPrivate
{
public:
    void setValue(QVariantMap &parent, const QString &path, const QVariant &value);
    QVariant getValue(const QString &path) const;

public:
    QVariantMap root;
};

class HDictionary
{
public:
    explicit HDictionary();
    virtual ~HDictionary();

public:
    void set(const QString &path, const QVariant &value);
    QVariant get(const QString &path);

public:
    void fromVariantMap(const QVariantMap &);
    void fromJsonObject(const QJsonObject &);
    QVariantMap toVariantMap();
    QJsonObject toJsonObject();

protected:
    QScopedPointer<HDictionaryPrivate> d_ptr;

protected:
    friend QDebug operator<<(QDebug, const HDictionary &);
};

QDebug operator<<(QDebug, const HDictionary &);

HE_END_NAMESPACE

