/***************************************************************************************************
**      2019-10-23  HStreamHelper 流帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QDataStream>
#include <functional>

HE_BEGIN_NAMESPACE

class HStreamHelper
{
public:
    template<typename K, typename T>
    static bool read(QDataStream &s, QMap<K, T *> &data, std::function<T *(QString)> create);

    template<typename K, typename T>
    static bool write(QDataStream &s, QMap<K, T *> data);
};

template<typename K, typename T>
bool HStreamHelper::read(QDataStream &s, QMap<K, T *> &data, std::function<T *(QString)> create)
{
    quint32 size;
    QString type;
    K key;

    data.clear();
    s >> size;
    for (quint32 i = 0; i < size; i++)
    {
        s >> key >> type;
        auto item = create(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            data.clear();
            return false;
        }
        data.insert(key, item);
    }
    return true;
}

template<typename K, typename T>
bool HStreamHelper::write(QDataStream &s, QMap<K, T *> data)
{
    s << quint32(data.size());
    for (auto i = data.begin(); i != data.end(); i++)
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
    return true;
}

HE_END_NAMESPACE
