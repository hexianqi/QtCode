#include "HJsonTree_p.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QJsonArray>
#include <QtCore/QtDebug>

HE_BEGIN_NAMESPACE

// 读取属性的值
QJsonValue HJsonTreePrivate::getValue(const QString &path, const QJsonObject &fromNode) const
{
    // 确定搜索的根节点，如果fromNode为空则搜索的根节点为root
    auto parent = fromNode.isEmpty() ? root : fromNode;
    // 把path使用分隔符'.'分解成多个属性名字
    auto names = path.split('.');
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
void HJsonTreePrivate::setValue(const QString &path, const QJsonValue &value, QJsonObject &parent)
{
    auto index = path.indexOf('.');
    auto property = path.left(index);
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
        auto child = fieldValue.toObject();
        setValue(restPath, value, child);
        // 因为 QJsonObject 操作的都是对象的副本，所以递归结束后需要保存起来再次设置回parent
        fieldValue = child;
    }
    // 如果不存在则会创建
    parent[property] = fieldValue;
}

void HJsonTreePrivate::setError(const QString &value)
{
    valid = false;
    errorString = value;
}

void HJsonTreePrivate::remove(const QString &path, QJsonObject &parent)
{
    auto index = path.indexOf('.');
    auto property = path.left(index);
    auto restPath = (index > 0) ? path.mid(index + 1) : QString();

    if(restPath.isEmpty())
    {
        // 找到要删除的属性
        parent.remove(property);
    }
    else
    {
        // 路径中间的属性，递归访问它的子属性
        auto child = parent[property].toObject();
        remove(restPath, child);
        parent[property] = child;
    }
}

void HJsonTreePrivate::fromJson(QByteArray &data)
{
    QJsonParseError error;
    doc = QJsonDocument::fromJson(data, &error);
    if (error.error == QJsonParseError::NoError)
        root = doc.object();
    else
        setError(QString("%1\nOffset: %2").arg(error.errorString()).arg(error.offset));
}

HJsonTree::HJsonTree(QObject *parent) :
    QObject(parent),
    d_ptr(new HJsonTreePrivate)
{
}

HJsonTree::HJsonTree(HJsonTreePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HJsonTree::~HJsonTree() = default;

HJsonTree *HJsonTree::fromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        auto json = new HJsonTree;
        json->d_ptr->setError(QString("Cannot open the file: %1").arg(fileName));
        return json;
    }
    auto data = file.readAll();
    return fromJson(data);
}

HJsonTree *HJsonTree::fromString(const QString &text)
{
    auto data = text.toUtf8();
    return fromJson(data);
}

HJsonTree *HJsonTree::fromJson(QByteArray &data)
{
    auto json = new HJsonTree;
    json->d_ptr->fromJson(data);
    return json;
}

bool HJsonTree::isValid() const
{
    return d_ptr->valid;
}

QString HJsonTree::errorString() const
{
    return d_ptr->errorString;
}

int HJsonTree::getInt(const QString &path, int defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toInt(defaultValue);
}

bool HJsonTree::getBool(const QString &path, bool defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toBool(defaultValue);
}

double HJsonTree::getDouble(const QString &path, double defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toDouble(defaultValue);
}

QString HJsonTree::getString(const QString &path, const QString &defaultValue, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toString(defaultValue);
}

QVariant HJsonTree::getVariant(const QString &path, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toVariant();
}

QStringList HJsonTree::getStringList(const QString &path, const QJsonObject &fromNode) const
{
    QStringList list;
    auto array = getJsonArray(path, fromNode);
    for (auto i : array)
        list << i.toString();
    return list;
}

QVariantList HJsonTree::getVariantList(const QString &path, const QJsonObject &fromNode) const
{
    return getJsonArray(path, fromNode).toVariantList();
}

QJsonValue HJsonTree::getJsonValue(const QString &path, const QJsonObject &fromNode) const
{
    return d_ptr->getValue(path, fromNode);
}

QJsonArray HJsonTree::getJsonArray(const QString &path, const QJsonObject &fromNode) const
{
    // 如果根节点是数组时特殊处理
    if ((path == "." || path == "") && fromNode.isEmpty())
        return d_ptr->doc.array();
    return getJsonValue(path, fromNode).toArray();
}

QJsonObject HJsonTree::getJsonObject(const QString &path, const QJsonObject &fromNode) const
{
    return getJsonValue(path, fromNode).toObject();
}

QJsonValue HJsonTree::get(const QString &path) const
{
    return d_ptr->getValue(path, d_ptr->root);
}

void HJsonTree::set(const QString &path, const QJsonValue &value)
{
    d_ptr->setValue(path, value, d_ptr->root);
}

void HJsonTree::set(const QString &path, const QVariant &value)
{
    d_ptr->setValue(path, QJsonValue::fromVariant(value), d_ptr->root);
}

void HJsonTree::set(const QString &path, const QStringList &value)
{
    d_ptr->setValue(path, QJsonArray::fromStringList(value), d_ptr->root);
}

void HJsonTree::set(const QString &path, const QVariantList &value)
{
    d_ptr->setValue(path, QJsonArray::fromVariantList(value), d_ptr->root);
}

void HJsonTree::remove(const QString &path)
{
    d_ptr->remove(path, d_ptr->root);
}

void HJsonTree::save(const QString &fileName, bool compact) const
{
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << toString(compact);
    out.flush();
    file.close();
}

QString HJsonTree::toString(bool compact) const
{
    return QJsonDocument(d_ptr->root).toJson(compact ? QJsonDocument::Compact : QJsonDocument::Indented);
}

QDebug operator<<(QDebug dbg, const HJsonTree &)
{
//    HDumpTree::dump(s.d.root, "root");
    return dbg.maybeSpace();
}

HE_END_NAMESPACE
