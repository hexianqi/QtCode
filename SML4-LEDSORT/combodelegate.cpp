#include "combodelegate.h"
#include <qcombobox.h>

ComboDelegate::ComboDelegate(QStringList lstdata,QObject *parent)
    : QItemDelegate(parent)
{
    lsttext = lstdata;  //�����б��ַ���
}

QWidget *ComboDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QComboBox *editor = new QComboBox(parent);
    for(qint8 i=0;i<lsttext.count();i++)
    {
        editor->addItem(lsttext.at(i)); //ע����value(i).toLatin1()�����ܳ������룬��ʹlsttext�Ѿ�����ǰfromutf8��

//        editor->addItem(QString::fromLocal8Bit(lsttext.value(i).toLatin1()));
    }

    editor->installEventFilter(const_cast<ComboDelegate*>(this));

    return editor;
}

void ComboDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    QString str = index.model()->data(index).toString();
    
    QComboBox *box = static_cast<QComboBox*>(editor);
    int i = box->findText(str);
    box->setCurrentIndex(i);
}

void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    QString str = box->currentText();

    model->setData(index, str);
}

void ComboDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

