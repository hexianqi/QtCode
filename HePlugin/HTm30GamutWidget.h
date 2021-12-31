/***************************************************************************************************
**      2021-12-27  HTm30GamutWidget
***************************************************************************************************/

#pragma once

#include "HCartesianWidget.h"

class HTm30GamutWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30GamutWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30GamutWidget)

public:
    explicit HTm30GamutWidget(QWidget *parent = nullptr);
    ~HTm30GamutWidget() override;

public:
    QStringList dataType();
    void setData(const QVariantMap &value);

public:
    bool isDrawBackground() const;
    bool isDrawEdge() const;
    bool isDrawHueBin() const;
    bool isDrawVector() const;

protected:
    bool drawElse(QPainter *) override;
    bool drawBackground(QPainter *);
    bool drawEdge(QPainter *);
    bool drawHueBin(QPainter *);
    bool drawCross(QPainter *);
    bool drawVector(QPainter *);

private:
    void init();
};



