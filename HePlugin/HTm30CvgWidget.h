/***************************************************************************************************
**      2021-12-08  HTm30CvgWidget
***************************************************************************************************/

#pragma once

#include "HCartesianWidget.h"

class HTm30CvgWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30CvgWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30CvgWidget)

public:
    explicit HTm30CvgWidget(QWidget *parent = nullptr);
    ~HTm30CvgWidget() override;

public:
    bool isDrawBackground() const;
    bool isDrawEdge() const;
    bool isDrawLabel() const;
    bool isDrawCircle_10_20() const;
    bool isDrawVector() const;
    bool isDrawQuiver() const;
    bool isDrawValue() const;

protected:
    bool drawElse(QPainter *) override;
    bool drawBackground(QPainter *);
    bool drawEdge(QPainter *);
    bool drawLabel(QPainter *);
    bool drawCross(QPainter *);
    bool drawCircle_10_20(QPainter *);
    bool drawVector(QPainter *);
    bool drawQuiver(QPainter *);
    bool drawValue(QPainter *);

private:
    void init();
};



