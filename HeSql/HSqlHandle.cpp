#include "HSqlHandle_p.h"
#include "ISqlTableModel.h"
#include "IProductInfo.h"
#include "HProductInfoDialog.h"
#include "HSqlFindDialog.h"
#include <QtCore/QDateTime>
#include <QtSql/QSqlRecord>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSqlHandle::HSqlHandle(QObject *parent) :
    ISqlHandle(parent),
    d_ptr(new HSqlHandlePrivate)
{
}


HSqlHandle::HSqlHandle(HSqlHandlePrivate &p, QObject *parent) :
    ISqlHandle(parent),
    d_ptr(&p)
{
}

HSqlHandle::~HSqlHandle()
{
    qDebug() << __func__;
}

void HSqlHandle::initialize(QVariantMap /*param*/)
{
}

QString HSqlHandle::typeName()
{
    return "HSqlHandle";
}

void HSqlHandle::setModel(ISqlTableModel *p)
{
    if (d_ptr->model == p)
        return;
    d_ptr->model = p;
}

void HSqlHandle::setFieldFind(QStringList value)
{
    if (d_ptr->fieldFinds == value)
        return;
    d_ptr->fieldFinds = value;
}

void HSqlHandle::setProductInfo(IProductInfo *p)
{
    if (d_ptr->productInfo == p)
        return;
    d_ptr->productInfo = p;
}

QStringList HSqlHandle::field()
{
    return d_ptr->model->field();
}

bool HSqlHandle::addRecord(QVariantMap value)
{
    if (d_ptr->productInfo->editable())
        editProductInfo();

    auto r = d_ptr->model->record();
    for (auto f : field())
    {
        if (f == "ID")
            continue;
        if (d_ptr->productInfo->contains(f))
            r.setValue(f, d_ptr->productInfo->data(f));
        else if (value.contains(f))
            r.setValue(f, value.value(f));
        else if (f == "TestDateTime")
            r.setValue(f, QDateTime::currentDateTime());
        else if (f == "TestDate")
            r.setValue(f, QDate::currentDate());
        else if (f == "TestTime")
            r.setValue(f, QTime::currentTime());
    }

    if (!d_ptr->model->insertRecord(-1, r))
        return false;
    d_ptr->productInfo->saveOnce();
    d_ptr->model->resetCurrentRow(d_ptr->model->rowCount() - 1);
    return true;
}

void HSqlHandle::removeRecord()
{
    auto row = d_ptr->model->currentRow();
    if (d_ptr->model->removeRow(row))
    {
        d_ptr->model->submitAll();
        d_ptr->model->resetCurrentRow(row);
    }
}

void HSqlHandle::removeRecord(int row, int count)
{
    if (d_ptr->model->removeRows(row, count))
    {
        d_ptr->model->submitAll();
        d_ptr->model->resetCurrentRow(row);
    }
}

void HSqlHandle::revertRecord()
{
    setFilter("");
}

void HSqlHandle::findRecord()
{
    HSqlFindDialog dlg(d_ptr->fieldFinds, d_ptr->model->filter());
    if (dlg.exec())
        setFilter(dlg.filter());
}

void HSqlHandle::editProductInfo()
{
    HProductInfoDialog dlg;
    dlg.setData(d_ptr->productInfo);
    dlg.exec();
}

void HSqlHandle::setFilter(QString value)
{
    d_ptr->model->setFilter(value);
    d_ptr->model->select();
    d_ptr->model->resetCurrentRow(0);
}

HE_SQL_END_NAMESPACE
