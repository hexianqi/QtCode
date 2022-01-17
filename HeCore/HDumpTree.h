/***************************************************************************************************
**      2021-12-23  HDumpTree 树状打印数据。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HDumpTreePrivate;

class HDumpTree : public QObject
{
    Q_OBJECT

public:
    explicit HDumpTree(QObject *parent = nullptr);
    ~HDumpTree() override;

public:
    static void dump(const QVariant &value, const QString &name = QString());
    static void dump(const QJsonValue &value, const QString &name = QString());
    static void dumpChild(const QObject *);
    static void dumpProperty(const QObject *);

protected:
    QScopedPointer<HDumpTreePrivate> d_ptr;
};

HE_END_NAMESPACE

