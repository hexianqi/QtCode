#pragma once

#include "HJsonTree.h"
#include <QtCore/QJsonDocument>

HE_BEGIN_NAMESPACE

class HJsonTreePrivate
{
public:
    QJsonValue getValue(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    void setValue(const QString &path, const QJsonValue &value, QJsonObject &parent);
    void setError(const QString &);
    void remove(const QString &path, QJsonObject &parent);
    void fromJson(QByteArray &data);

public:
    QJsonDocument doc;      // Json 的文档对象
    QJsonObject root;       // Json 的根节点
    bool valid = true;      // Json 是否有效
    QString errorString;    // Json 无效时的错误信息
};

HE_END_NAMESPACE

