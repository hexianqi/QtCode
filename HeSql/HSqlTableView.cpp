#include "HSqlTableView_p.h"
#include "ISqlTableModel.h"
#include "HSql.h"
#include "HePlugin/HOptionalTableExtend.h"
#include <QtWidgets/QHeaderView>

HE_BEGIN_NAMESPACE

HSqlTableView::HSqlTableView(QWidget *parent) :
    HTableView(*new HSqlTableViewPrivate, parent)
{
    init();
}

HSqlTableView::~HSqlTableView() = default;

void HSqlTableView::setModel(ISqlTableModel *model)
{
    Q_D(HSqlTableView);
    HTableView::setModel(model);
    auto field = model->field();
    auto display = HSql::toType(field);
    field.removeAll("ID");
    field.removeAll("EnergyGraph");
    field.removeAll("ReflectGraph");
    auto optional = HSql::toType(field);
    d->optionalExtend->setDisplay(display);
    d->optionalExtend->setOptional(optional);
    d->optionalExtend->setSelected(optional);
    connect(model, &ISqlTableModel::currentRowChanged, this, &HSqlTableView::selectRow);
    connect(selectionModel(), &QItemSelectionModel::currentRowChanged, this, [=](QModelIndex index){ model->setCurrentRow(index.row()); });
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

HE_END_NAMESPACE
