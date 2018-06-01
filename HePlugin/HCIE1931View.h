#ifndef HCIE1931VIEW_H
#define HCIE1931VIEW_H

#include "HZoomChartView.h"

class HCIE1931ViewPrivate;

class QDESIGNER_WIDGET_EXPORT HCIE1931View : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCIE1931View)

public:
    explicit HCIE1931View(QWidget *parent = nullptr);
    ~HCIE1931View();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;

protected slots:
    void updatePosition(QPointF pos);

private:
    void init();
};

#endif // HCIE1931VIEW_H
