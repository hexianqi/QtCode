#include "HAbstractTableExtend_p.h"

HAbstractTableExtend::HAbstractTableExtend(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractTableExtendPrivate)
{
}

HAbstractTableExtend::HAbstractTableExtend(HAbstractTableExtendPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractTableExtend::~HAbstractTableExtend() = default;

void HAbstractTableExtend::setTableView(QTableView *v)
{
    if (d_ptr->view == v)
        return;
    d_ptr->view = v;
}

QTableView *HAbstractTableExtend::tableView()
{
    return d_ptr->view;
}
