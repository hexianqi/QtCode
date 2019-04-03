/***************************************************************************************************
**      2019-04-03  HGraphicsItem   自定义图样项。
***************************************************************************************************/

#ifndef HGRAPHICSITEM_H
#define HGRAPHICSITEM_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QGraphicsItem>

class HGraphicsItemPrivate;

class QDESIGNER_WIDGET_EXPORT HGraphicsItem : public QGraphicsItem
{
public:
    explicit HGraphicsItem(QGraphicsItem *parent = nullptr);
    ~HGraphicsItem() override;

protected:
    HGraphicsItem(HGraphicsItemPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    QScopedPointer<HGraphicsItemPrivate> d_ptr;
};

#endif // HGRAPHICSITEM_H
