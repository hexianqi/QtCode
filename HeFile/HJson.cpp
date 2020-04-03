#include "HJson_p.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QJsonArray>

HE_FILE_BEGIN_NAMESPACE

// 读取属性的值
QJsonValue HJsonPrivate::getValue(const QString &path, const QJsonObject &fromNode) const
{
    // 确定搜索的根节点，如果fromNode为空则搜索的根节点为root
    auto parent = fromNode.isEmpty() ? root : fromNode;
    // 把path使用分隔符 . 分解成多个属性名字
    auto names  = path.split('.');
    // 从搜索的根节点开始向下查找到倒数第二个属性名字对应的QJsonObject parent
    auto size = names.size();
    for (int i = 0; i < size - 1; ++i)
    {
        if (parent.isEmpty())
            return QJsonValue();
        parent = parent.value(names.at(i)).toObject();
    }
    // 返回parent中属性名为倒数第一个属性名字对应的属性值
    return parent.value(names.last());
}

// 使用递归加引用设置 Json 的值，因为toObject()等返回的是对象的副本，对其修改不会改变原来的对象，所以需要用引用来实现
void HJsonPrivate::setValue(QJsonObject &parent, const QString &path, const QJsonValue &value)
{
    // 第一个 . 的位置
    auto index   = path.indexOf('.');
    // 第一个 . 之前的内容
    auto property = path.left(index);
    // 第一个 . 后面的内容
    auto restPath = (index > 0) ? path.mid(index + 1) : QString();

    auto fieldValue = parent.value(property);
    if (restPath.isEmpty())
    {
        // 找到要设置的属性
        fieldValue = value;
    }
    else
    {
        // 路径中间的属性，递归访问它的子属性
        auto obj = fieldValue.toObject();
        setValue(obj, restPath, value);
        // 因为 QJsonObject 操作的都是对象的副本，所以递归结束后需要保存起来再次设置回parent
        fieldValue = obj;
    }
    // 如果不存在则会创建
    parent[property] = fieldValue;
}

void HJsonPrivate::setError(const QString &value)
{
    valid = false;
    errorString = value;
}

HJson::HJson() :
    d_ptr(new HJsonPrivate)
{
}

HJson::HJson(HJsonPrivate &p) :
    d_ptr(&p)
{
}

HJson::~HJson()
{
}


HJson *HJson::fromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        auto json = new HJson;
        json->d_ptr->setError(QString("Cannot open the file: %1").arg(fileName));
        return json;
    }
    auto data = file.readAll();
    return fromJson(data);
}

HJson *HJson::fromString(const QString &text)
{
    auto data = text.toUtf8();
    return fromJson(data);
}

HJson *HJson::fromJson(QByteArray &data)
{
    QJsonParseError error;
    auto json = new HJson;
    json->d_ptr->doc = QJsonDocument::fromJson(data, &error);

    if (error.error == QJsonParseError::NoError)
        json->d_ptr->root = json->d_ptr->doc.object();
    else
        json->d_ptr->setError(QString("%1\nOffset: %2").arg(error.errorString()).arg(error.offset));
    return json;
}

bool HJson::isValid() const
{
    return d_ptr->valid;
}

QString HJson::errorString() const
{
    return d_ptr->errorString;
}

int HJson::getInt(const QString &path, int defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toInt(defaultValue);
}

bool HJson::getBool(const QString &path, bool defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toBool(defaultValue);
}

double HJson::getDouble(const QString &path, double defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toDouble(defaultValue);
}

QString HJson::getString(const QString &path, const QString &defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toString(defaultValue);
}

QStringList HJson::getStringList(const QString &path, const QJsonObject &fromNode) const
{
    QStringList list;
    auto array = getJsonValue(path, fromNode).toArray();
    for (int i = 0; i < array.size(); i++)
        list << array[i].toString();
    return list;
}

QJsonObject HJson::getJsonObject(const QString &path, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toObject();
}

QJsonValue HJson::getJsonValue(const QString &path, const QJsonObject &fromNode) const
{
    return d_ptr->getValue(path, fromNode);
}

QJsonArray HJson::getJsonArray(const QString &path, const QJsonObject &fromNode) const
{
    // 如果根节点是数组时特殊处理
    if ((path == "." || path == "") && fromNode.isEmpty())
        return d_ptr->doc.array();
    return getJsonValue(path, fromNode).toArray();
}

void HJson::setValue(const QString &path, const QJsonValue &value)
{
    d_ptr->setValue(d_ptr->root, path, value);
}

void HJson::setValue(const QString &path, const QStringList &value)
{
    d_ptr->setValue(d_ptr->root, path, QJsonArray::fromStringList(value));
}

void HJson::saveFile(const QString &fileName, bool pretty) const
{
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << toString(pretty);
    out.flush();
    file.close();
}

QString HJson::toString(bool pretty) const
{
    return QJsonDocument(d_ptr->root).toJson(pretty ? QJsonDocument::Indented : QJsonDocument::Compact);
}

HE_FILE_END_NAMESPACE
