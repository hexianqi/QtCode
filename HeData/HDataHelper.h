/***************************************************************************************************
**      2019-05-22  HDataHelper 数据帮助类。
***************************************************************************************************/

#ifndef HDATAHELPER_H
#define HDATAHELPER_H

#include "HDataGlobal.h"
#include <QtCore/QDataStream>
#include <functional>

HE_DATA_BEGIN_NAMESPACE

class HDataHelper
{
public:
    static quint16 readUInt16(QVector<uchar> data, int &pos);
    static QVector<uchar> writeUInt16(quint16 data);
    static bool checkHead(QVector<uchar> data, int &pos, int &version);

    template<typename K, typename T>
    static bool read(QDataStream &s, QMap<K, T *> &data, std::function<T *(QString)> func);

    template<typename K, typename T>
    static bool write(QDataStream &s, QMap<K, T *> data);
};

template<typename K, typename T>
bool HDataHelper::read(QDataStream &s, QMap<K, T *> &data, std::function<T *(QString)> func)
{
    quint32 size;
    QString type;
    K key;

    data.clear();
    s >> size;
    for (quint32 i = 0; i < size; i++)
    {
        s >> key >> type;
        auto item = func(type);
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
bool HDataHelper::write(QDataStream &s, QMap<K, T *> data)
{
    s << quint32(data.size());
    for (auto i = data.begin(); i != data.end(); i++)
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
    return true;
}

HE_DATA_END_NAMESPACE

#endif // HDATAHELPER_H
