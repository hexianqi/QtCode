/***************************************************************************************************
**      2019-04-03  HGraphicsItem   自定义图样项。
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QGraphicsItem>

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
