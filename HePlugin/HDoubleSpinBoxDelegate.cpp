#include "HDoubleSpinBoxDelegate_p.h"
#include "HPluginHelper.h"
#include <QtWidgets/QDoubleSpinBox>

HDoubleSpinBoxDelegate::HDoubleSpinBoxDelegate(QObject *parent) :
    HItemDelegate(*new HDoubleSpinBoxDelegatePrivate, parent)
{
}

HDoubleSpinBoxDelegate::HDoubleSpinBoxDelegate(HDoubleSpinBoxDelegatePrivate &p, QObject *parent) :
    HItemDelegate(p, parent)
{
}

QWidget *HDoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return HItemDelegate::createEditor(parent, option, index);

    auto type = toType(index);
    auto editor = new QDoubleSpinBox(parent);
    HPluginHelper::initWidget(type, editor);
    connect(editor, &QDoubleSpinBox::editingFinished, this, &HItemDelegate::editingFinished);
    return editor;
}

void HDoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return QItemDelegate::setEditorData(editor, index);

    auto spinBox = qobject_cast<QDoubleSpinBox *>(editor);
    auto value = index.model()->data(index, Qt::EditRole).toDouble();
    spinBox->setValue(value);
}

void HDoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return QItemDelegate::setModelData(editor, model, index);

    auto spinBox = qobject_cast<QDoubleSpinBox *>(editor);
    spinBox->interpretText();
    model->setData(index, QString::number(spinBox->value(), 'f', spinBox->decimals()), Qt::EditRole);
}
