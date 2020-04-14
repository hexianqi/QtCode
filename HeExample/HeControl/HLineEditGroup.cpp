#include "HLineEditGroup_p.h"
#include <QtWidgets/QLineEdit>

HE_CONTROL_BEGIN_NAMESPACE

HLineEditGroup::HLineEditGroup(QObject *parent) :
    QObject(parent),
    d_ptr(new HLineEditGroupPrivate)
{
}

HLineEditGroup::HLineEditGroup(HLineEditGroupPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HLineEditGroup::~HLineEditGroup() = default;

void HLineEditGroup::addLineEdit(QLineEdit *p)
{
    if (d_ptr->lineEdits.contains(p))
        return;
    d_ptr->lineEdits.append(p);
    connect(p, &QLineEdit::returnPressed, this, &HLineEditGroup::next);
}

void HLineEditGroup::removeLineEdit(QLineEdit *p)
{
    if (!d_ptr->lineEdits.contains(p))
        return;
    disconnect(p, &QLineEdit::returnPressed, this, &HLineEditGroup::next);
    d_ptr->lineEdits.removeOne(p);
}

QList<QLineEdit *> HLineEditGroup::lineEdits() const
{
    return d_ptr->lineEdits;
}

void HLineEditGroup::next()
{
    if (d_ptr->lineEdits.size() < 2)
        return;
    auto lineEdit = qobject_cast<QLineEdit *>(sender());
    auto index = d_ptr->lineEdits.indexOf(lineEdit);
    if (index == -1)
        return;
    index += 1;
    if (index >= d_ptr->lineEdits.size())
        index = 0;
    d_ptr->lineEdits.at(index)->setFocus();
}

HE_CONTROL_END_NAMESPACE
