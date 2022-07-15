#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

//在tableview中添加combobox控件

#include <QtGui>
#include <qitemdelegate.h>

class ComboDelegate : public QItemDelegate
{
    Q_OBJECT

private:
    QStringList lsttext;    //初始化时传入的下拉列表字符串，zhb20210925增加

public:
    ComboDelegate(QStringList lstdata,QObject *parent = 0);//初始化时传入的下拉列表字符串，zhb20210925增加，注意带默认值的参数必须放在后面，否则会报错

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif
