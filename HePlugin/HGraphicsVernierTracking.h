/***************************************************************************************************
**      2018-07-03  HGraphicsVernierTracking Graphics游标追踪策略。
***************************************************************************************************/

#ifndef HGRAPHICSVERNIERTRACKING_H
#define HGRAPHICSVERNIERTRACKING_H

#include "HAbstractVernierTracking.h"

class QGraphicsItem;
class HGraphicsVernierTrackingPrivate;

class HGraphicsVernierTracking : public HAbstractVernierTracking
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGraphicsVernierTracking)

public:
    explicit HGraphicsVernierTracking(Qt::Orientation orientation, QGraphicsItem *gpatent = nullptr, QWidget *parent = nullptr);
    ~HGraphicsVernierTracking() override;

public:
    bool setEnable(bool b) override;
    bool setValidRegion(QRectF value) override;
    bool setOrientation(Qt::Orientation value) override;
    bool setVernierColor(const QColor &value) override;
    bool setVernier(int i, double percent) override;
    void resizeVernier(int size) override;

public:
    bool mouseMoveEvent(QMouseEvent *) override;

protected:
    HGraphicsVernierTracking(HGraphicsVernierTrackingPrivate &p, QWidget *parent = nullptr);

protected:
    void setLinesVisible(bool b);
    void setLinesColor(QColor color);
    void setLine(int pos);
    void setLines();
};

#endif // HGRAPHICSVERNIERTRACKING_H
