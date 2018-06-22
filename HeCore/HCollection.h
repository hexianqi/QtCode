/***************************************************************************************************
**      2018-06-19  HCollection 集合模板。
***************************************************************************************************/

#ifndef HCOLLECTION_H
#define HCOLLECTION_H

#include "ICollection.h"

HE_CORE_BEGIN_NAMESPACE

template <class T>
class HCollection : virtual public ICollection<T>
{
public:
    HCollection();
    ~HCollection();
public:
    virtual void initialize(QVariantMap param) override;
    virtual void clear() override;
    virtual bool contains(QString name) override;
    virtual void insert(QString name, T *value) override;
    virtual T *first() override;
    virtual T *value(QString name) override;
    virtual QList<T *> values() override;

protected:
    QScopedPointer<QMap<QString, T *>> _datas;
};

template <class T>
inline HCollection<T>::HCollection()
    : _datas(new QMap<QString, T *>)
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
        QMapIterator<QString, QVariant> i(param.value("datas").toMap());
        while (i.hasNext())
        {
            i.next();
            insert(i.key(), FromVariant(T, i.value()));
        }
    }
}

template<class T>
inline void HCollection<T>::clear()
{
    _datas->clear();
}

template<class T>
inline bool HCollection<T>::contains(QString name)
{
    return _datas->contains(name);
}

template <class T>
inline void HCollection<T>::insert(QString name, T *value)
{
    _datas->insert(name, value);
}

template<class T>
inline T *HCollection<T>::first()
{
    return _datas->first();
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
