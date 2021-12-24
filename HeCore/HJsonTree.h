/***************************************************************************************************
**      2021-12-23  HJsonTree 树结构访问Json（可以按"."）。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>
#include <QtCore/QJsonObject>

HE_BEGIN_NAMESPACE

class HJsonTreePrivate;

class HJsonTree : public QObject
{
    Q_OBJECT

public:
    ~HJsonTree() override;

public:
    static HJsonTree *fromFile(const QString &fileName);
    static HJsonTree *fromString(const QString &text);
    static HJsonTree *fromJson(QByteArray &data);

public:
    bool isValid() const;
    QString errorString() const;

public:
    int             getInt(const QString &path, int defaultValue = 0, const QJsonObject &fromNode = QJsonObject()) const;
    bool            getBool(const QString &path, bool defaultValue = false, const QJsonObject &fromNode = QJsonObject()) const;
    double          getDouble(const QString &path, double defaultValue = 0.0, const QJsonObject &fromNode = QJsonObject()) const;
    QString         getString(const QString &path, const QString &defaultValue = QString(), const QJsonObject &fromNode = QJsonObject()) const;
    QVariant        getVariant(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QStringList     getStringList(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QVariantList    getVariantList(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QJsonValue      getJsonValue(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QJsonArray      getJsonArray(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QJsonObject     getJsonObject(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;

public:
    QJsonValue get(const QString &path) const;
    void set(const QString &path, const QJsonValue &value);
    void set(const QString &path, const QVariant &value);
    void set(const QString &path, const QStringList &value);
    void set(const QString &path, const QVariantList &value);
    void remove(const QString &path);
    void save(const QString &fileName, bool compact = true) const;
    QString toString(bool compact = true) const;

protected:
    explicit HJsonTree(QObject *parent = nullptr);
    HJsonTree(HJsonTreePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HJsonTreePrivate> d_ptr;

protected:
    friend QDebug operator<<(QDebug, const HJsonTree &);
};

QDebug operator<<(QDebug, const HJsonTree &);

HE_END_NAMESPACE

