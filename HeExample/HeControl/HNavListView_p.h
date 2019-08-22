#ifndef HNAVLISTVIEW_P_H
#define HNAVLISTVIEW_P_H

#include "HNavListView.h"
#include <QtWidgets/QStyledItemDelegate>

HE_CONTROL_BEGIN_NAMESPACE

class HNavListViewPrivate
{

};

class HNavDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit HNavDelegate(QObject *parent = nullptr);
    ~HNavDelegate() override;

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    HNavListView *_view;
    QFont _iconFont;
};

class HNavModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit HNavModel(QObject *parent = nullptr);
    ~HNavModel() override;

public:
    struct TreeNode
    {
        int level;                  // 层级,父节点-1,子节点-2
        bool expand;                // 是否打开子节点
        bool last;                  // 是否末尾元素
        QChar icon;                 // 左侧图标
        QString text;               // 显示的节点文字
        QString tip;                // 右侧描述文字
        QString parentText;         // 父节点名称
        QList<TreeNode *> children; // 子节点集合
    };

    struct ListNode
    {
        QString text;               // 节点文字
        TreeNode *treeNode;         // 节点指针
    };

public slots:
    void setItem(const QStringList &value);
    void expand(const QModelIndex &index);

protected:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    void refreshList();

private:
    QList<TreeNode *> _treeNode;
    QList<ListNode> _listNode;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVLISTVIEW_P_H
