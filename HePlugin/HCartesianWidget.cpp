#include "HCartesianWidget_p.h"
#include "HRubberBand.h"
#include <QMouseEvent>

HCartesianWidgetPrivate::HCartesianWidgetPrivate(HCartesianWidget *q)
    : HDiagramWidgetPrivate(q)
{

}

HCartesianWidget::HCartesianWidget(QWidget *parent)
    : HDiagramWidget(*new HCartesianWidgetPrivate(this), parent)
{
    init();
}

HCartesianWidget::HCartesianWidget(HCartesianWidgetPrivate &p, QWidget *parent)
    : HDiagramWidget(p, parent)
{
    init();
}

HCartesianWidget::~HCartesianWidget()
{
}

void HCartesianWidget::mousePressEvent(QMouseEvent *e)
{
    Q_D(HCartesianWidget);
    d->rubberBand->mousePressEvent(e);
    HDiagramWidget::mousePressEvent(e);
}

void HCartesianWidget::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCartesianWidget);
    d->rubberBand->mouseMoveEvent(e);
    HDiagramWidget::mouseMoveEvent(e);
}

void HCartesianWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HCartesianWidget);
    d->rubberBand->mouseReleaseEvent(e);
    HDiagramWidget::mouseReleaseEvent(e);
}

void HCartesianWidget::init()
{
    Q_D(HCartesianWidget);
    d->rubberBand = new HRubberBand(this);

}

