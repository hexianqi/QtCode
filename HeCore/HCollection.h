/***************************************************************************************************
**      2018-06-19  HCollection 集合模板。
***************************************************************************************************/

#ifndef HCOLLECTION_H
#define HCOLLECTION_H

#include "ICollection.h"

HE_CORE_BEGIN_NAMESPACE

template <typename T>
class HCollection : virtual public ICollection<T>
{
public:
    HCollection();
    ~HCollection();

public:
    void initialize(QVariantMap param) override;
    void clear() override;
    bool contains(QString name) override;
    void insert(QString name, T *value) override;
    T *first() override;
    T *value(QString name) override;
    QList<T *> values() override;

protected:
    QScopedPointer<QMap<QString, T *>> _datas;
};

template <typename T>
HCollection<T>::HCollection()
    : _datas(new QMap<QString, T *>)
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
        QMapIterator<QString, QVariant> i(param.value("datas").toMap());
        while (i.hasNext())
        {
            i.next();
            insert(i.key(), FromVariant(T, i.value()));
        }
    }
}

template <typename T>
void HCollection<T>::clear()
{
    _datas->clear();
}

template <typename T>
bool HCollection<T>::contains(QString name)
{
    return _datas->contains(name);
}

template <typename T>
void HCollection<T>::insert(QString name, T *value)
{
    _datas->insert(name, value);
}

template <typename T>
T *HCollection<T>::first()
{
    return _datas->first();
}

template <typename T>
T *HCollection<T>::value(QString name)
{
    return _datas->value(name);
}

template <typename T>
QList<T *> HCollection<T>::values()
{
    return _datas->values();
}

HE_CORE_END_NAMESPACE

#endif // HCOLLECTION_H
