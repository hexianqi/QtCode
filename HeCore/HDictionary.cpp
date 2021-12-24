#include "HDictionary.h"
#include "HDumpTree.h"
#include <QtCore/QJsonObject>
#include <QtCore/QtDebug>

HE_BEGIN_NAMESPACE

void HDictionaryPrivate::setValue(QVariantMap &parent, const QString &path, const QVariant &value)
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
        auto child = fieldValue.toMap();
        setValue(child, restPath, value);
        // 因为 QVariantMap 操作的都是对象的副本，所以递归结束后需要保存起来再次设置回parent
        fieldValue = child;
    }
    // 如果不存在则会创建
    parent[property] = fieldValue;
}

QVariant HDictionaryPrivate::getValue(const QString &path) const
{
    auto parent = root;
    // 把path使用分隔符 . 分解成多个属性名字
    auto names  = path.split('.');
    // 从搜索的根节点开始向下查找到倒数第二个属性名字对应的QVariantMap parent
    auto size = names.size();
    for (int i = 0; i < size - 1; ++i)
    {
        if (parent.isEmpty())
            return QVariant();
        parent = parent.value(names.at(i)).toMap();
    }
    // 返回parent中属性名为倒数第一个属性名字对应的属性值
    return parent.value(names.last());
}

HDictionary::HDictionary()
{
}

HDictionary::~HDictionary()
{
}

void HDictionary::set(const QString &path, const QVariant &value)
{
    d.setValue(d.root, path, value);
}

QVariant HDictionary::get(const QString &path)
{
    return d.getValue(path);
}

void HDictionary::fromVariantMap(const QVariantMap &value)
{
    d.root = value;
}

void HDictionary::fromJsonObject(const QJsonObject &value)
{
    d.root = value.toVariantMap();
}

QVariantMap HDictionary::toVariantMap()
{
    return d.root;
}

QJsonObject HDictionary::toJsonObject()
{
    return QJsonObject::fromVariantMap(d.root);
}

QDebug operator<<(QDebug dbg, const HDictionary &s)
{
    HDumpTree::dump(s.d.root, "root");
    return dbg.maybeSpace();
}

HE_END_NAMESPACE
