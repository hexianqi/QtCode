#include "HOptionalTableExtend_p.h"
#include "HTypeOptionalDialog.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QTableView>

HOptionalTableExtend::HOptionalTableExtend(QObject *parent) :
    HAbstractTableExtend(*new HOptionalTableExtendPrivate, parent)
{
}

void HOptionalTableExtend::setTableView(QTableView *p)
{
    HAbstractTableExtend::setTableView(p);
    auto optional = new QAction(QIcon(":/image/Options.png"), tr("显示选项(&O)..."));
    connect(optional, &QAction::triggered, this, &HOptionalTableExtend::editSelected);
    p->addAction(optional);
}

void HOptionalTableExtend::setDisplay(const QStringList &value)
{
    Q_D(HOptionalTableExtend);
    if (d->displays == value)
        return;
    d->displays = value;
}

void HOptionalTableExtend::setOptional(const QStringList &value)
{
    Q_D(HOptionalTableExtend);
    if (d->optionals == value)
        return;
    d->optionals = value;
}

void HOptionalTableExtend::setSelected(const QStringList &value)
{
    Q_D(HOptionalTableExtend);
    if (d->selecteds == value)
        return;
    d->selecteds = value;
    setColumnHidden();
}

QStringList HOptionalTableExtend::selected()
{
    Q_D(HOptionalTableExtend);
    return d->selecteds;
}

void HOptionalTableExtend::editSelected()
{
    Q_D(HOptionalTableExtend);
    HTypeOptionalDialog dlg(d->selecteds, d->optionals);
    if (dlg.exec())
        setSelected(dlg.selected());
}

void HOptionalTableExtend::setColumnHidden()
{
    Q_D(HOptionalTableExtend);
    if (d->view == nullptr)
        return;
    for (int i = 0; i < d->displays.size(); i++)
        d->view->setColumnHidden(i, !d->selecteds.contains(d->displays[i]));
}
