#ifndef HCARTESIANWIDGET_H
#define HCARTESIANWIDGET_H

#include "HDiagramWidget.h"

class HCartesianWidgetPrivate;

class HCartesianWidget : public HDiagramWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCartesianWidget)

public:
    explicit HCartesianWidget(QWidget *parent = nullptr);
    ~HCartesianWidget();

protected:
    HCartesianWidget(HCartesianWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *) override;

private:
    void init();
};

#endif // HCARTESIANWIDGET_H
