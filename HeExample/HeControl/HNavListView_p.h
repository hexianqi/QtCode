#pragma once

#include "HNavListView.h"
#include <QtWidgets/QStyledItemDelegate>

HE_CONTROL_BEGIN_NAMESPACE

class HNavListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit HNavListModel(QObject *parent = nullptr);
    ~HNavListModel() override;

public:
    struct HTreeNode
    {
        int level;                  // 层级,父节点-1,子节点-2
        bool expand;                // 是否打开子节点
        bool last;                  // 是否末尾元素
        QChar icon;                 // 左侧图标
        QString text;               // 显示的节点文字
        QString tip;                // 右侧描述文字
        QString parentText;         // 父节点名称
        QList<HTreeNode *> childs;  // 子节点集合
    };

    struct HListNode
    {
        QString text;               // 节点文字
        HTreeNode *node;            // 节点指针
    };

public slots:
    void readData(const QString &fileName);
    void setItem(const QStringList &value);
    void expand(const QModelIndex &index);

protected:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    void refreshList();

private:
    QList<HTreeNode *> _treeNodes;
    QList<HListNode *> _listNodes;
};

class HNavListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit HNavListDelegate(QObject *parent = nullptr);

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const;
    void drawLine(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const;
    void drawTriangle(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const;
    void drawSeparate(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const;
    void drawText(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const;
    void drawTip(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const;
    void drawIcon(QPainter *painter, const QStyleOptionViewItem &option, HNavListModel::HTreeNode *node) const;

private:
    HNavListView *_view;
    QFont _iconFont;
};

class HNavListViewPrivate
{
public:
    QString items;
    bool rightIconVisible = true;
    bool tipVisible = true;
    int tipWidth = 40;
    bool separateVisible = true;
    int separateHeight = 1;
    QColor separateColor = QColor(40, 43, 51);
    bool lineVisible = true;
    bool lineLeft = true;
    int lineWidth = 6;
    QColor lineColor = QColor(0, 187, 158);
    bool triangleVisible = true;
    bool triangleLeft = false;
    int triangleWidth = 6;
    QColor triangleColor = QColor(250, 250, 250);
    int parentMargin = 10;
    int parentIconMargin = 30;
    int parentFontSize = 12;
    int parentHeight = 35;
    QColor parentNormalColor = QColor(57, 61, 73);
    QColor parentSelectedColor = QColor(78, 83, 102);
    QColor parentHoverColor = QColor(78, 83, 102);
    QColor parentTextNormalColor = QColor(250, 250, 250);
    QColor parentTextSelectedColor = QColor(250, 250, 250);
    QColor parentTextHoverColor = QColor(250, 250, 250);
    int childMargin = 15;
    int childIconMargin = 35;
    int childFontSize = 12;
    int childHeight = 30;
    QColor childNormalColor = QColor(40, 43, 51);
    QColor childSelectedColor = QColor(20, 20, 20);
    QColor childHoverColor = QColor(20, 20, 20);
    QColor childTextNormalColor = QColor(180, 180, 180);
    QColor childTextSelectedColor = QColor(250, 250, 250);
    QColor childTextHoverColor = QColor(255, 255, 255);
    HNavListView::ExpendMode expendMode = HNavListView::ExpendMode_SingleClick;

    HNavListModel *model;
    HNavListDelegate *delegate;
};

HE_CONTROL_END_NAMESPACE

Q_DECLARE_METATYPE(HE_CONTROL_NAMESPACE::HNavListModel::HTreeNode *)
