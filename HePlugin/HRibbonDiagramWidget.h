#pragma once

#include "HCartesianWidget.h"

class HRibbonDiagramWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HRibbonDiagramWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HRibbonDiagramWidget)

public:
    explicit HRibbonDiagramWidget(QWidget *parent = nullptr);

public:
    virtual void setVisibleRibbon(bool b);
    virtual void setDrawRibbon(bool b);
    virtual void setPolygonRibbon(const QPolygonF &value, bool refresh = true);

public:
    bool isDrawRibbon();

protected:
    HRibbonDiagramWidget(HRibbonDiagramWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual bool drawElse(QPainter *);
    virtual bool drawRibbon(QPainter *);

private:
    void init();
};
