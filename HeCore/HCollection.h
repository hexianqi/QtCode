/***************************************************************************************************
**      2018-06-19  HCollection 集合模板。
***************************************************************************************************/

#pragma once

#include "ICollection.h"
#include "HDefine.h"

HE_CORE_BEGIN_NAMESPACE

template <typename T>
class HCollectionPrivate
{
public:
    QMap<QString, T *> items;
};

template <typename T>
class HCollection : public ICollection<T>
{
public:
    HCollection();
    ~HCollection();

public:
    void initialize(QVariantMap param) override;

public:
    void clear() override;
    bool contains(QString key) override;
    int size() override;
    bool isEmpty() override;
    void insert(QString key, T *value) override;
    int remove(QString key) override;
    T *first() override;
    T *value(QString key) override;
    T *item(QString key) override;
    T *itemAt(int index) override;
    QStringList keys() override;
    QList<T *> values() override;

protected:
    HCollection(HCollectionPrivate<T> &);

protected:
    QScopedPointer<HCollectionPrivate<T>> d_ptr;
};

template <typename T>
HCollection<T>::HCollection() :
    d_ptr(new HCollectionPrivate<T>())
{
}

template <typename T>
HCollection<T>::HCollection(HCollectionPrivate<T> &p) :
    d_ptr(&p)
{
}

template <typename T>
HCollection<T>::~HCollection()
{
}

template <typename T>
void HCollection<T>::initialize(QVariantMap param)
{
    if (param.contains("datas"))
    {
        auto value = param.value("datas").toMap();
        for (auto i = value.begin(); i != value.end(); i++)
            insert(i.key(), FromVariant(T, i.value()));
    }
}

template <typename T>
void HCollection<T>::clear()
{
    d_ptr->items.clear();
}

template <typename T>
bool HCollection<T>::contains(QString key)
{
    return d_ptr->items.contains(key);
}

template <typename T>
int HCollection<T>::size()
{
    return d_ptr->items.size();
}

template<typename T>
bool HCollection<T>::isEmpty()
{
    return d_ptr->items.isEmpty();
}

template <typename T>
void HCollection<T>::insert(QString key, T *value)
{
    d_ptr->items.insert(key, value);
}

template <typename T>
int HCollection<T>::remove(QString key)
{
    return d_ptr->items.remove(key);
}

template <typename T>
T *HCollection<T>::first()
{
    return d_ptr->items.first();
}

template <typename T>
T *HCollection<T>::value(QString key)
{
    return d_ptr->items.value(key, nullptr);
}

template <typename T>
T *HCollection<T>::item(QString key)
{
    return value(key);
}

template <typename T>
T *HCollection<T>::itemAt(int index)
{
    if (index < 0 || index >= size())
        return nullptr;
    return values().at(index);
}

template <typename T>
QStringList HCollection<T>::keys()
{
    return d_ptr->items.keys();
}

template <typename T>
QList<T *> HCollection<T>::values()
{
    return d_ptr->items.values();
}

HE_CORE_END_NAMESPACE
