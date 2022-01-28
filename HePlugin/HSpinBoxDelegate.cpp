#include "HSpinBoxDelegate_p.h"
#include "HPluginHelper.h"
#include <QtWidgets/QSpinBox>

HSpinBoxDelegate::HSpinBoxDelegate(QObject *parent) :
    HStyledItemDelegate(*new HSpinBoxDelegatePrivate, parent)
{
}

HSpinBoxDelegate::HSpinBoxDelegate(HSpinBoxDelegatePrivate &p, QObject *parent) :
    HStyledItemDelegate(p, parent)
{
}

QWidget *HSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return HStyledItemDelegate::createEditor(parent, option, index);

    auto type = toType(index);
    auto editor = new QSpinBox(parent);
    HPluginHelper::initWidget(type, editor);
    return editor;
}

void HSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return HStyledItemDelegate::setEditorData(editor, index);

    auto spinBox = qobject_cast<QSpinBox *>(editor);
    auto value = index.model()->data(index, Qt::EditRole).toInt();
    spinBox->setValue(value);
}

void HSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return HStyledItemDelegate::setModelData(editor, model, index);

    auto spinBox = qobject_cast<QSpinBox *>(editor);
    spinBox->interpretText();
    model->setData(index, spinBox->value(), Qt::EditRole);
}
