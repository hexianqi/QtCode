#include "HSqlTableView_p.h"
#include "ISqlTableModel.h"
#include "HSql.h"
#include "HePlugin/HOptionalTableExtend.h"
#include <QtWidgets/QHeaderView>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSqlTableView::HSqlTableView(QWidget *parent) :
    HTableView(*new HSqlTableViewPrivate, parent)
{
    init();
}

HSqlTableView::~HSqlTableView()
{
    qDebug() << __func__;
}

void HSqlTableView::setModel(ISqlTableModel *model)
{
    Q_D(HSqlTableView);
    HTableView::setModel(model);
    auto field = model->fields();
    auto display = toType(field);
    field.removeAll("ID");
    field.removeAll("EnergyGraph");
    auto optional = toType(field);
    d->optionalExtend->setDisplay(display);
    d->optionalExtend->setOptional(optional);
}

void HSqlTableView::init()
{
    Q_D(HSqlTableView);
    d->optionalExtend = new HOptionalTableExtend(this);
    d->optionalExtend->setTableView(this);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ContiguousSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setStretchLastSection(true);
}

HE_SQL_END_NAMESPACE
