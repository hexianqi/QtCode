#ifndef HRIBBONDIAGRAMWIDGET_H
#define HRIBBONDIAGRAMWIDGET_H

#include "HCartesianWidget.h"

class HRibbonDiagramWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HRibbonDiagramWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HRibbonDiagramWidget)

public:
    explicit HRibbonDiagramWidget(QWidget *parent = nullptr);
    ~HRibbonDiagramWidget();

public:
    virtual void setPolygonRibbon(QPolygonF value);

protected:
    HRibbonDiagramWidget(HRibbonDiagramWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual bool drawElse(QPainter *);
    virtual bool drawRibbon(QPainter *);

private:
    void init();
};

#endif // HRIBBONDIAGRAMWIDGET_H
