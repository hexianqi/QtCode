#ifndef HVERNIERWIDGET_H
#define HVERNIERWIDGET_H

#include "HCartesianWidget.h"

class HVernierWidgetPrivate;
class HVernierTracking;

class HVernierWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HVernierWidget)

public:
    explicit HVernierWidget(QWidget *parent = nullptr);
    ~HVernierWidget();

public:
    HVernierTracking *tracking();

protected:
    HVernierWidget(HVernierWidgetPrivate &p, QWidget *parent = nullptr);

private:
    void init();
};

#endif // HVERNIERWIDGET_H
