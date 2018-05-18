#ifndef HCOLLECTION_H
#define HCOLLECTION_H

#include "ICollection.h"

HE_CORE_BEGIN_NAMESPACE

// 集合模板
template <class T>
class HCollection : virtual public ICollection<T>
{
public:
    HCollection();
    ~HCollection();
public:
    virtual void initialize(QVariantMap param) override;
    virtual void insert(QString name, T *value) override;
    virtual T *value(QString name) override;
    virtual QList<T *> values() override;

protected:
    QScopedPointer<QHash<QString, T *>> _datas;
};

template <class T>
inline HCollection<T>::HCollection()
    : _datas(new QHash<QString, T *>)
{
}

template <class T>
inline HCollection<T>::~HCollection()
{
}

template <class T>
inline void HCollection<T>::initialize(QVariantMap param)
{
    if (param.contains("datas"))
    {
        QHashIterator<QString, QVariant> i(param.value("datas").toHash());
        while (i.hasNext())
        {
            i.next();
            insert(i.key(), FromVariant(T, i.value()));
        }
    }
}

template <class T>
inline void HCollection<T>::insert(QString name, T *value)
{
    _datas->insert(name, value);
}

template <class T>
inline T *HCollection<T>::value(QString name)
{
    return _datas->value(name);
}

template <class T>
inline QList<T *> HCollection<T>::values()
{
    return _datas->values();
}

HE_CORE_END_NAMESPACE

#endif // HCOLLECTION_H
