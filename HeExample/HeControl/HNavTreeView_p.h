#ifndef HNAVTREEVIEW_P_H
#define HNAVTREEVIEW_P_H

#include "HNavTreeView.h"
#include <QtWidgets/QStyledItemDelegate>

class QStandardItemModel;

HE_CONTROL_BEGIN_NAMESPACE

class HNavTreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit HNavTreeDelegate(QObject *parent = nullptr);
    ~HNavTreeDelegate() override;

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option) const;
    void drawIcon(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawTip(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    HNavTreeView *_view;
    QStandardItemModel *_model;
    QFont _iconFont;
};

class HNavTreeViewPrivate
{
public:
    QColor lineColor = QColor("#404244");
    QColor normalBackground = QColor("#31495A");
    QColor hoverBackground = QColor("#77D8C4");
    QColor selectedBackground = QColor("#18BD9B");
    QColor normalTextColor = QColor("#F0F0F0");
    QColor hoverTextColor = QColor("#000000");
    QColor selectedTextColor = QColor("#F0F0F0");
    QStandardItemModel *model;
    QMap<QString, QString> infos;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVTREEVIEW_P_H
