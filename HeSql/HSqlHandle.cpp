#include "HSqlHandle_p.h"
#include "ISqlTableModel.h"
#include "HSqlFindDialog.h"
#include "HeCore/HCore.h"
#include <QtCore/QDateTime>
#include <QtSql/QSqlRecord>

HE_BEGIN_NAMESPACE

HSqlHandle::HSqlHandle(QObject *parent) :
    QObject(parent),
    d_ptr(new HSqlHandlePrivate)
{
}

HSqlHandle::HSqlHandle(HSqlHandlePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HSqlHandle::~HSqlHandle() = default;

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
    if (d_ptr->fieldFind == value)
        return;
    d_ptr->fieldFind = value;
}

QStringList HSqlHandle::field()
{
    return d_ptr->model->field();
}

bool HSqlHandle::addRecord(QVariantMap value)
{
    auto r = d_ptr->model->record();
    for (const auto &f : field())
        r.setValue(f, value.value(f));

    if (!d_ptr->model->insertRecord(-1, r))
        return false;
    d_ptr->model->submitAll();
    d_ptr->model->resetCurrentRow(0);
    return true;


//    if (edit && d_ptr->productInfo->editable())
//        editProductInfo();

//    auto r = d_ptr->model->record();
//    for (const auto &f : field())
//    {
//        if (f == "ID")
//            continue;
//        if (value.contains(f) && value.value(f).isValid())
//        {
//            if (f == "EnergyGraph")
//                r.setValue(f, toString(value.value(f).value<QPolygonF>()));
//            else
//                r.setValue(f, value.value(f));
//        }
//        else if (d_ptr->productInfo->contains(f))
//            r.setValue(f, d_ptr->productInfo->data(f));
//        else if (f == "TestDateTime")
//            r.setValue(f, QDateTime::currentDateTime());
//        else if (f == "TestDate")
//            r.setValue(f, QDate::currentDate());
//        else if (f == "TestTime")
//            r.setValue(f, QTime::currentTime());
//    }

//    if (!d_ptr->model->insertRecord(-1, r))
//        return false;
//    d_ptr->productInfo->saveOnce();
//    d_ptr->model->submitAll();
//    d_ptr->model->resetCurrentRow(0);
//    return true;
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
    HSqlFindDialog dlg(d_ptr->fieldFind, d_ptr->model->filter());
    if (dlg.exec())
        setFilter(dlg.filter());
}

void HSqlHandle::setFilter(const QString &value)
{
    d_ptr->model->setFilter(value);
    d_ptr->model->select();
    d_ptr->model->resetCurrentRow(0);
}

QString HSqlHandle::toString(QPolygonF value)
{
    QStringList list;
    for (auto p : value)
        list << HCore::toString("[波长]", p.x()) + ":" +  HCore::toString("[光谱能量百分比]", p.y());
    return list.join(",");
}

HE_END_NAMESPACE
