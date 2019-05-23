/***************************************************************************************************
**      2019-04-28  HAdjustDetail 数据详情模板。
***************************************************************************************************/

#ifndef HDATADETAIL_H
#define HDATADETAIL_H

#include "IDataDetail.h"
#include "IDataEditWidget.h"
#include "HeData/IDataCollection.h"
#include "HeData/IFileStream.h"

HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

template <typename T>
class HDataDetailPrivate
{
public:
    IDataEditWidget<T> *widget = nullptr;
    IDataCollection<T> *datas = nullptr;
    T *data = nullptr;
};

template <typename T>
class HDataDetail : public IDataDetail
{
public:
    explicit HDataDetail(QWidget *parent = nullptr);
    ~HDataDetail();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;
    QWidget *editWidget() override;
    void start() override;
    void importFile() override;
    void exportFile() override;
    void addItem(QString name) override;
    void delItem(QString name) override;
    void setCurrentItem(QString name) override;
    void saveData() override;
    virtual void setEditWidget(IDataEditWidget<T> *);
    virtual void setData(IDataCollection<T> *);

protected:
    HDataDetail(HDataDetailPrivate<T> &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HDataDetailPrivate<T>> d_ptr;
};

template <typename T>
HDataDetail<T>::HDataDetail(QWidget *parent) :
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
HDataDetail<T>::~HDataDetail()
{
}

template<typename T>
void HDataDetail<T>::initialize(QVariantMap /*param*/)
{

}

template<typename T>
QString HDataDetail<T>::typeName()
{
    return QString("HDataDetail<T>");
}

template<typename T>
QWidget *HDataDetail<T>::editWidget()
{
    return d_ptr->widget;
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
    if (d_ptr->datas->fileStream()->openFile())
        emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

template <typename T>
void HDataDetail<T>::exportFile()
{
    saveData();
    d_ptr->datas->fileStream()->saveAsFile();
}

template <typename T>
void HDataDetail<T>::addItem(QString name)
{
    auto data = d_ptr->widget->createData();
    d_ptr->datas->insert(name, data);
    emit sourceChanged(d_ptr->datas->keys(), name);
}

template <typename T>
void HDataDetail<T>::delItem(QString name)
{
    d_ptr->widget->clearData();
    if (d_ptr->datas->remove(name) > 0)
        emit sourceChanged(d_ptr->datas->keys(), name);
}

template <typename T>
void HDataDetail<T>::setCurrentItem(QString name)
{
    saveData();
    d_ptr->datas->setUseIndex(name);
    d_ptr->data = d_ptr->datas->value(name);
    d_ptr->widget->setData(d_ptr->datas->value(name));
}

template<typename T>
void HDataDetail<T>::saveData()
{
    d_ptr->widget->saveData();
}

template<typename T>
void HDataDetail<T>::setEditWidget(IDataEditWidget<T> *p)
{
    if (d_ptr->widget == p)
        return;
    d_ptr->widget = p;
}

template<typename T>
void HDataDetail<T>::setData(IDataCollection<T> *p)
{
    if (d_ptr->datas == p)
        return;
    d_ptr->datas = p;
    emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

HE_GUI_END_NAMESPACE

#endif // HDATADETAIL_H
