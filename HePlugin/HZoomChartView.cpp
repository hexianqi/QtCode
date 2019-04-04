#include "HZoomChartView_p.h"
#include <QAction>

HZoomChartView::HZoomChartView(QWidget *parent) :
    HChartView(*new HZoomChartViewPrivate, nullptr, parent)
{
    init();
}

HZoomChartView::HZoomChartView(QChart *chart, QWidget *parent) :
    HChartView(*new HZoomChartViewPrivate, chart, parent)
{
    init();
}

HZoomChartView::HZoomChartView(HZoomChartViewPrivate &p, QChart *chart, QWidget *parent) :
    HChartView(p, chart, parent)
{
    init();
}

HZoomChartView::~HZoomChartView()
{
}

void HZoomChartView::resizeEvent(QResizeEvent *e)
{
    if (scene())
    {
        auto size = e->size();
        scene()->setSceneRect(QRect(QPoint(0, 0), size));
        chart()->resize(size);
    }
    QChartView::resizeEvent(e);
}

void HZoomChartView::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
        e->accept();
    else
        QChartView::mouseReleaseEvent(e);
}

void HZoomChartView::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Backspace:
        chart()->zoomReset();
        break;
    default:
        QChartView::keyPressEvent(e);
        break;
    }
}

void HZoomChartView::init()
{
    Q_D(HZoomChartView);
    d->actionZoomReset = new QAction(QIcon(":/image/Zoom.png"), tr("还原(&R)"));
    d->actionZoomIn = new QAction(QIcon(":/image/ZoomIn.png"), tr("放大(&I)"));
    d->actionZoomOut = new QAction(QIcon(":/image/ZoomOut.png"), tr("缩小(&O)"));
    connect(d->actionZoomReset, &QAction::triggered, this, [=] { chart()->zoomReset(); });
    connect(d->actionZoomIn, &QAction::triggered, this, [=] { chart()->zoomIn(); });
    connect(d->actionZoomOut, &QAction::triggered, this, [=] { chart()->zoomOut(); });
    addAction(d->actionZoomReset);
    addAction(d->actionZoomIn);
    addAction(d->actionZoomOut);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setRubberBand(QChartView::RectangleRubberBand);
}
