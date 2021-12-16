/***************************************************************************************************
**      2019-04-28  HAdjustDetail 数据详情模板。
***************************************************************************************************/

#pragma once

#include "IDataDetail.h"
#include "IDataEditer.h"
#include "HeData/IDataCollection.h"
#include "HeData/IMultStream.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

template <typename T>
class HDataDetailPrivate
{
public:
    IDataEditer<T> *editer = nullptr;
    IDataCollection<T> *datas = nullptr;
    T *data = nullptr;
};

template <typename T>
class HDataDetail : public IDataDetail
{
public:
    explicit HDataDetail(QObject *parent = nullptr);
    ~HDataDetail() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;
    QWidget *widget() override;
    void start() override;
    void importFile() override;
    void exportFile() override;
    void addItem(QString name) override;
    void delItem(QString name) override;
    void setCurrentItem(QString name) override;
    void saveData() override;
    virtual void setEditer(IDataEditer<T> *);
    virtual void setData(IDataCollection<T> *);

protected:
    HDataDetail(HDataDetailPrivate<T> &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HDataDetailPrivate<T>> d_ptr;
};

template <typename T>
HDataDetail<T>::HDataDetail(QObject *parent) :
    IDataDetail(parent),
    d_ptr(new HDataDetailPrivate<T>)
{
}

template<typename T>
HDataDetail<T>::HDataDetail(HDataDetailPrivate<T> &p, QWidget *parent) :
    IDataDetail(parent),
    d_ptr(&p)
{
}

template <typename T>
HDataDetail<T>::~HDataDetail() = default;

template<typename T>
void HDataDetail<T>::initialize(QVariantMap /*param*/)
{

}

template<typename T>
QString HDataDetail<T>::typeName()
{
    return "HDataDetail<T>";
}

template<typename T>
QWidget *HDataDetail<T>::widget()
{
    return d_ptr->editer->widget();
}

template <typename T>
void HDataDetail<T>::start()
{
    if (d_ptr->datas != nullptr)
        emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

template <typename T>
void HDataDetail<T>::importFile()
{
    if (d_ptr->datas->multStream()->openFile())
        emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

template <typename T>
void HDataDetail<T>::exportFile()
{
    saveData();
    d_ptr->datas->multStream()->saveAsFile();
}

template <typename T>
void HDataDetail<T>::addItem(QString name)
{
    auto data = d_ptr->editer->createData();
    if (data == nullptr)
        return;
    d_ptr->datas->insert(name, data);
    emit sourceChanged(d_ptr->datas->keys(), name);
}

template <typename T>
void HDataDetail<T>::delItem(QString name)
{
    d_ptr->editer->clearData();
    if (d_ptr->datas->remove(name) > 0)
        emit sourceChanged(d_ptr->datas->keys(), name);
}

template <typename T>
void HDataDetail<T>::setCurrentItem(QString name)
{
    saveData();
    d_ptr->datas->setUseIndex(name);
    d_ptr->data = d_ptr->datas->value(name);
    d_ptr->editer->setData(d_ptr->datas->value(name));
}

template<typename T>
void HDataDetail<T>::saveData()
{
    d_ptr->editer->saveData();
}

template<typename T>
void HDataDetail<T>::setEditer(IDataEditer<T> *p)
{
    if (d_ptr->editer == p)
        return;
    d_ptr->editer = p;
}

template<typename T>
void HDataDetail<T>::setData(IDataCollection<T> *p)
{
    if (d_ptr->datas == p)
        return;
    d_ptr->datas = p;
    emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

HE_END_NAMESPACE
