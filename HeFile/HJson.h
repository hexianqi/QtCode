/***************************************************************************************************
**      2020-03-30  HJson
**                  Qt 的 JSON API 读写多层次的属性不够方便，这个类的目的就是能够使用带 "." 的路径格式访问 Json 的属性，
**
**                  例如: "id"访问的是根节点下的id，"user.address.street" 访问根节点下user的address的street 的属性。
**                  JSON 例子(JSON 的 key 必须用双引号括起来，值有不同的类型，数值类型不用双引号括起来，字符类型的才用)：
**                  {
**                      "id": 18191,
**                      "user": {
**                          "address": {
**                          "street": "Wiessenstrasse",
**                          "postCode": "100001"
**                          },
**                          "childrenNames": ["Alice", "Bob", "John"]
**                      }
**                  }
**                  访问 id:              json.getInt("id")，返回 18191
**                  访问 street:          json.getString("user.address.street")，返回 "Wiessenstrasse"
**                  访问 childrenNames:   json.getStringList("user.childrenNames") 得到字符串列表("Alice", "Bob", "John")
**                  设置 user.address.postCode 则可以使用 json.set("user.address.postCode", "056231")
**                  如果根节点是数组，则使用 json.getJsonArray(".") 获取
**
**                  如果读取的属性不存在，则返回指定的默认值，如 "database.username.firstName" 不存在，
**                  调用 json.getString("database.username.firstName", "defaultName")，由于要访问的属性不存在，
**                  得到的是一个空的 QJsonValue，所以返回我们指定的默认值 "defaultName"。
**
**                  如果要修改的属性不存在，则会自动的先创建属性，然后设置它的值。
**
**                  注意: JSON 文件要使用 UTF-8 编码。
***************************************************************************************************/

#ifndef HJSON_H
#define HJSON_H

#include "HFileGlobal.h"
#include <QtCore/QScopedPointer>
#include <QtCore/QJsonObject>

HE_FILE_BEGIN_NAMESPACE

class HJsonPrivate;

class HE_FILE_EXPORT HJson
{
public:
    static HJson *fromFile(const QString &fileName);
    static HJson *fromString(const QString &text);
    static HJson *fromJson(QByteArray &data);

public:
    virtual ~HJson();

public:
    bool isValid() const;
    QString errorString() const;

    int         getInt(const QString &path, int defaultValue = 0, const QJsonObject &fromNode = QJsonObject()) const;
    bool        getBool(const QString &path, bool defaultValue = false, const QJsonObject &fromNode = QJsonObject()) const;
    double      getDouble(const QString &path, double defaultValue = 0.0, const QJsonObject &fromNode = QJsonObject()) const;
    QString     getString(const QString &path, const QString &defaultValue = QString(), const QJsonObject &fromNode = QJsonObject()) const;
    QStringList getStringList(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QJsonObject getJsonObject(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QJsonValue  getJsonValue(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;
    QJsonArray  getJsonArray(const QString &path, const QJsonObject &fromNode = QJsonObject()) const;

public:
    void setValue(const QString &path, const QJsonValue &value);
    void setValue(const QString &path, const QStringList &value);
    void saveFile(const QString &fileName, bool pretty = true) const;
    QString toString(bool pretty = true) const;

protected:
    HJson();
    HJson(HJsonPrivate &);

protected:
    QScopedPointer<HJsonPrivate> d_ptr;
};

HE_FILE_END_NAMESPACE

#endif // HJSON_H
