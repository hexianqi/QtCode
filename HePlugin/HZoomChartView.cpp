#include "HZoomChartView_p.h"
#include <QAction>

HZoomChartViewPrivate::HZoomChartViewPrivate(HZoomChartView *q)
    : q_ptr(q)
{
}

HZoomChartView::HZoomChartView(QWidget *parent)
    : QChartView(parent), d_ptr(new HZoomChartViewPrivate(this))
{
    init();
}

HZoomChartView::HZoomChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent), d_ptr(new HZoomChartViewPrivate(this))
{
    init();
}

HZoomChartView::HZoomChartView(HZoomChartViewPrivate &p, QWidget *parent)
    : QChartView(parent), d_ptr(&p)
{
    init();
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

HZoomChartView::~HZoomChartView()
{
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
    d_ptr->actionZoomReset = new QAction(tr("还原(&R)"));
    d_ptr->actionZoomIn = new QAction(QIcon(":/image/ZoomIn.png"), tr("放大(&I)"));
    d_ptr->actionZoomOut = new QAction(QIcon(":/image/ZoomOut.png"), tr("缩小(&O)"));
    connect(d_ptr->actionZoomReset, &QAction::triggered, this, [=] { chart()->zoomReset(); });
    connect(d_ptr->actionZoomIn, &QAction::triggered, this, [=] { chart()->zoomIn(); });
    connect(d_ptr->actionZoomOut, &QAction::triggered, this, [=] { chart()->zoomOut(); });
    addAction(d_ptr->actionZoomReset);
    addAction(d_ptr->actionZoomIn);
    addAction(d_ptr->actionZoomOut);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setRubberBand(QChartView::RectangleRubberBand);
}
