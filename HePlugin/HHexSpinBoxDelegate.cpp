#include "HHexSpinBoxDelegate_p.h"
#include "HHexSpinBox.h"
#include "HPluginHelper.h"

HHexSpinBoxDelegate::HHexSpinBoxDelegate(QObject *parent) :
    HItemDelegate(*new HHexSpinBoxDelegatePrivate, parent)
{
}

HHexSpinBoxDelegate::HHexSpinBoxDelegate(HHexSpinBoxDelegatePrivate &p, QObject *parent) :
    HItemDelegate(p, parent)
{
}

QWidget *HHexSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return HItemDelegate::createEditor(parent, option, index);

    auto type = toType(index);
    auto editor = new HHexSpinBox(parent);
    HPluginHelper::initWidget(type, editor);
    connect(editor, &HHexSpinBox::editingFinished, this, &HItemDelegate::editingFinished);
    return editor;
}

void HHexSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return QItemDelegate::setEditorData(editor, index);

    auto spinBox = qobject_cast<HHexSpinBox *>(editor);
    auto value = index.model()->data(index, Qt::EditRole).toInt();
    spinBox->setValue(value);
}

void HHexSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!isRedefine(index))
        return QItemDelegate::setModelData(editor, model, index);

    auto spinBox = qobject_cast<HHexSpinBox *>(editor);
    spinBox->interpretText();
    model->setData(index, QString::number(spinBox->value(), 16).toUpper(), Qt::EditRole);
}

