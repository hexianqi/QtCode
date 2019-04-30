/***************************************************************************************************
**      2019-04-28  HAdjustDetailWidget 抽象项详情窗体接口。
***************************************************************************************************/

#ifndef HABSTRACTDATADETAILWIDGET_H
#define HABSTRACTDATADETAILWIDGET_H

#include "IDataDetailWidget.h"
#include "IDataEditWidget.h"
#include "HeData/IDataCollection.h"
#include "HeData/IFileStream.h"

HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

template <typename T>
class HAbstractDataDetailWidgetPrivate
{
public:
    IDataEditWidget<T> *widget = nullptr;
    IDataCollection<T> *datas = nullptr;
    T *data = nullptr;
};

template <typename T>
class HAbstractDataDetailWidget : public IDataDetailWidget
{
public:
    explicit HAbstractDataDetailWidget(QWidget *parent = nullptr);
    ~HAbstractDataDetailWidget();

public:
    void start() override;
    void importFile() override;
    void exportFile() override;
    void addItem(QString name) override;
    void delItem(QString name) override;
    void setCurrentItem(QString name) override;
    void saveData() override;
    virtual void setData(IDataCollection<T> *);

protected:
    HAbstractDataDetailWidget(HAbstractDataDetailWidgetPrivate<T> &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractDataDetailWidgetPrivate<T>> d_ptr;
};

template <typename T>
HAbstractDataDetailWidget<T>::HAbstractDataDetailWidget(QWidget *parent) :
    IDataDetailWidget(parent),
    d_ptr(new HAbstractDataDetailWidgetPrivate<T>)
{
}

template<typename T>
HAbstractDataDetailWidget<T>::HAbstractDataDetailWidget(HAbstractDataDetailWidgetPrivate<T> &p, QWidget *parent) :
    IDataDetailWidget(parent),
    d_ptr(&p)
{
}

template <typename T>
HAbstractDataDetailWidget<T>::~HAbstractDataDetailWidget()
{
}

template <typename T>
void HAbstractDataDetailWidget<T>::start()
{
    if (d_ptr->datas != nullptr)
        emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

template <typename T>
void HAbstractDataDetailWidget<T>::importFile()
{
    if (d_ptr->datas->fileStream()->openFile())
        emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

template <typename T>
void HAbstractDataDetailWidget<T>::exportFile()
{
    saveData();
    d_ptr->datas->fileStream()->saveAsFile();
}

template <typename T>
void HAbstractDataDetailWidget<T>::addItem(QString name)
{
    auto data = d_ptr->widget->createData();
    d_ptr->datas->insert(name, data);
    emit sourceChanged(d_ptr->datas->keys(), name);
}

template <typename T>
void HAbstractDataDetailWidget<T>::delItem(QString name)
{
    d_ptr->widget->clearData();
    if (d_ptr->datas->remove(name) > 0)
        emit sourceChanged(d_ptr->datas->keys(), name);
}

template <typename T>
void HAbstractDataDetailWidget<T>::setCurrentItem(QString name)
{
    saveData();
    d_ptr->datas->setUseIndex(name);
    d_ptr->data = d_ptr->datas->value(name);
    d_ptr->widget->setData(d_ptr->datas->value(name));
}

template<typename T>
void HAbstractDataDetailWidget<T>::saveData()
{
    d_ptr->widget->saveData();
}

template<typename T>
void HAbstractDataDetailWidget<T>::setData(IDataCollection<T> *p)
{
    if (d_ptr->datas == p)
        return;
    d_ptr->datas = p;
    emit sourceChanged(d_ptr->datas->keys(), d_ptr->datas->useIndex());
}

HE_GUI_END_NAMESPACE

#endif // HABSTRACTDATADETAILWIDGET_H
