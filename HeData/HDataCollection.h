/***************************************************************************************************
**      2019-10-16
***************************************************************************************************/

#pragma once

#include "IDataCollection.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

template <typename T>
class HDataCollectionPrivate : public HCollectionPrivate<T>
{
public:
    IDataFactory *factory = nullptr;
    IDataStream *dataStream = nullptr;
    IMultStream *multStream = nullptr;
    QString useIndex;
};

template <typename T>
class HDataCollection : public IDataCollection<T>
{
    H_DECLARE_PRIVATE(HDataCollection, T)

public:
    HDataCollection();

public:
    IDataStream *dataStream() override;
    IMultStream *multStream() override;
    void setUseIndex(QString value) override;
    QString useIndex() override;
    T *useItem() override;

public:
    virtual bool readContent(QDataStream &);
    virtual bool writeContent(QDataStream &);

protected:
    HDataCollection(HDataCollectionPrivate<T> &);
};

template <typename T>
HDataCollection<T>::HDataCollection() :
    IDataCollection<T>(*new HDataCollectionPrivate<T>)
{
}

template<typename T>
HDataCollection<T>::HDataCollection(HDataCollectionPrivate<T> &p) :
    IDataCollection<T>(p)
{
}

template<typename T>
IDataStream *HDataCollection<T>::dataStream()
{
    H_D(HDataCollection, T);
    return d->dataStream;
}

template<typename T>
IMultStream *HDataCollection<T>::multStream()
{
    H_D(HDataCollection, T);
    return d->multStream;
}

template<typename T>
void HDataCollection<T>::setUseIndex(QString value)
{
    H_D(HDataCollection, T);
    if (d->useIndex == value || !this->contains(value))
        return;
    d->useIndex = value;
}

template<typename T>
QString HDataCollection<T>::useIndex()
{
    H_D(HDataCollection, T);
    return d->useIndex;
}

template<typename T>
T *HDataCollection<T>::useItem()
{
    H_D(HDataCollection, T);
    return this->item(d->useIndex);
}

template<typename T>
bool HDataCollection<T>::readContent(QDataStream &s)
{
    H_D(HDataCollection, T);
    if (d->dataStream == nullptr)
        return false;
    return d->dataStream->readContent(s);
}

template<typename T>
bool HDataCollection<T>::writeContent(QDataStream &s)
{
    H_D(HDataCollection, T);
    if (d->dataStream == nullptr)
        return false;
    return d->dataStream->writeContent(s);
}

HE_END_NAMESPACE
