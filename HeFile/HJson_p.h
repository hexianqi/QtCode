#ifndef HJSON_P_H
#define HJSON_P_H

#include "HJson.h"
#include <QtCore/QJsonDocument>

HE_FILE_BEGIN_NAMESPACE

class HJsonPrivate
{
public:
    QJsonValue getValue(const QString &path, const QJsonObject &fromNode) const;
    void setValue(QJsonObject &parent, const QString &path, const QJsonValue &value);
    void setError(const QString &value);
    void remove(QJsonObject &parent, const QString &path);

public:
    QJsonObject root;    // Json 的根节点
    QJsonDocument doc;   // Json 的文档对象
    bool valid = true;   // Json 是否有效
    QString errorString; // Json 无效时的错误信息
};

HE_FILE_END_NAMESPACE

#endif // HJSON_P_H
