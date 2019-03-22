#include "HDiagramWidget_p.h"
#include <QStylePainter>
#include <QResizeEvent>
#include <QStyleOptionFocusRect>

HDiagramWidgetPrivate::HDiagramWidgetPrivate(HDiagramWidget *q)
    : q_ptr(q)
{
}

QRectF HDiagramWidgetPrivate::calcPlotArea(QSize size)
{
    QRectF rect(margins.left(), margins.top(), size.width() - margins.left() - margins.right(), size.height() - margins.top() - margins.bottom());
    if (square)
    {
        auto side = qMin(rect.width(), rect.height());
        rect.adjust((rect.width() - side) / 2, (rect.height() - side) / 2, -(rect.width() - side) / 2, -(rect.height() - side) / 2);
    }
    return rect;
}

HDiagramWidget::HDiagramWidget(QWidget *parent)
    : QWidget(parent), d_ptr(new HDiagramWidgetPrivate(this))
{
    init();
}

HDiagramWidget::HDiagramWidget(HDiagramWidgetPrivate &p, QWidget *parent)
    : QWidget(parent), d_ptr(&p)
{
    init();
}

HDiagramWidget::~HDiagramWidget()
{
}

QSize HDiagramWidget::sizeHint() const
{
    return QSize(500, 500);
}

QSize HDiagramWidget::minimumSizeHint() const
{
    return QSize(350, 350);
}

void HDiagramWidget::setMargins(QMargins value)
{
    if (value.left() < 15)
        value.setLeft(15);
    if (value.right() < 15)
        value.setRight(15);
    if (value.top() < 15)
        value.setTop(15);
    if (value.bottom() < 15)
        value.setBottom(15);
    if (d_ptr->margins == value)
        return;
    d_ptr->margins = value;
    QResizeEvent event(size(), size());
    setMinimumSize(value.left() + value.right() + 200, value.top() + value.bottom() + 200);
    resizeEvent(&event);
}

void HDiagramWidget::setBrushBackground(QBrush value)
{
    if (d_ptr->brushBackground == value)
        return;
    d_ptr->brushBackground = value;
    refreshPixmap();
}

void HDiagramWidget::setBrushPlotArea(QBrush value)
{
    if (d_ptr->brushPlotArea == value)
        return;
    d_ptr->brushPlotArea = value;
    refreshPixmap();
}

void HDiagramWidget::setSquare(bool b)
{
    if (d_ptr->square == b)
        return;
    d_ptr->square = b;
    refreshPixmap();
}

void HDiagramWidget::setHalfSide(bool b)
{
    if (d_ptr->halfSide == b)
        return;
    d_ptr->halfSide = b;
    refreshPixmap();
}

void HDiagramWidget::setDrawFrame(bool b)
{
    if (d_ptr->drawFrame == b)
        return;
    d_ptr->drawFrame = b;
    refreshPixmap();
}

void HDiagramWidget::setDrawRuler(bool b)
{
    if (d_ptr->drawRuler == b)
        return;
    d_ptr->drawRuler = b;
    refreshPixmap();
}

void HDiagramWidget::setDrawGrid(bool b)
{
    if (d_ptr->drawGrid == b)
        return;
    d_ptr->drawGrid = b;
    refreshPixmap();
}

void HDiagramWidget::setColorFrame(QColor value)
{
    if (d_ptr->colorFrame == value)
        return;
    d_ptr->colorFrame = value;
    refreshPixmap();
}

void HDiagramWidget::setColorRuler(QColor value)
{
    if (d_ptr->colorRuler == value)
        return;
    d_ptr->colorRuler = value;
    refreshPixmap();
}

void HDiagramWidget::setColorGrid(QColor value)
{
    if (d_ptr->colorGrid == value)
        return;
    d_ptr->colorGrid = value;
    refreshPixmap();
}

QMargins HDiagramWidget::margins() const
{
    return d_ptr->margins;
}

QBrush HDiagramWidget::brushBackground() const
{
    return d_ptr->brushBackground;
}

QBrush HDiagramWidget::brushPlotArea() const
{
    return d_ptr->brushPlotArea;
}

bool HDiagramWidget::isSquare() const
{
    return d_ptr->square;
}

bool HDiagramWidget::isHalfSide() const
{
    return d_ptr->halfSide;
}

bool HDiagramWidget::isDrawFrame() const
{
    return d_ptr->drawFrame;
}

bool HDiagramWidget::isDrawRuler() const
{
    return d_ptr->drawRuler;
}

bool HDiagramWidget::isDrawGrid() const
{
    return d_ptr->drawGrid;
}

QColor HDiagramWidget::colorFrame() const
{
    return d_ptr->colorFrame;
}

QColor HDiagramWidget::colorRuler() const
{
    return d_ptr->colorRuler;
}

QColor HDiagramWidget::colorGrid() const
{
    return d_ptr->colorGrid;
}

void HDiagramWidget::setPolygon(int id, QPolygonF value, bool refresh)
{
    d_ptr->polygons.insert(id, value);
    if (refresh)
        refreshPixmap();
}

void HDiagramWidget::addPolygon(int id, QPolygonF value, QColor color, bool refresh)
{
    d_ptr->polygonColors.insert(id, color);
    setPolygon(id, value, refresh);
}

void HDiagramWidget::clearPolygon(int id)
{
    d_ptr->polygonColors.remove(id);
    d_ptr->polygons.remove(id);
    refreshPixmap();
}

void HDiagramWidget::setPlotArea(QRectF value)
{
    if (d_ptr->plotArea == value)
        return;
    d_ptr->plotArea = value;
    emit plotAreaChanged(value);
}

void HDiagramWidget::refreshPixmap(bool refresh)
{
    if (size().width() == 0 || size().height() == 0)
        return;

    d_ptr->pixmap = QPixmap(size());
    d_ptr->pixmap.fill(Qt::transparent);
    QPainter painter(&d_ptr->pixmap);

    initPixmap(&painter);
    drawFrame(&painter);
    drawRuler(&painter);
    drawPolygon(&painter);
    drawElse(&painter);
    drawGrid(&painter);

    if (refresh)
        update();
}

void HDiagramWidget::initPixmap(QPainter *painter)
{
    painter->initFrom(this);
    painter->setBrush(d_ptr->brushBackground);
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect());
}

bool HDiagramWidget::drawFrame(QPainter *painter)
{
    if (!isDrawFrame() || !d_ptr->plotArea.isValid())
        return false;

    QPen pen;
    pen.setColor(d_ptr->colorFrame);
    pen.setWidthF(2);
    pen.setStyle(Qt::NoPen);

    painter->save();
    painter->setPen(pen);
    painter->setBrush(d_ptr->brushPlotArea);
    painter->drawRect(d_ptr->plotArea);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(d_ptr->plotArea.bottomLeft(), d_ptr->plotArea.topLeft());
    painter->drawLine(d_ptr->plotArea.bottomLeft(), d_ptr->plotArea.bottomRight());
    if (!isHalfSide())
    {
        painter->drawLine(d_ptr->plotArea.topRight(), d_ptr->plotArea.topLeft());
        painter->drawLine(d_ptr->plotArea.topRight(), d_ptr->plotArea.bottomRight());
    }
    painter->restore();
    return true;
}

bool HDiagramWidget::drawRuler(QPainter *)
{
    if (!isDrawRuler() || !d_ptr->plotArea.isValid())
        return false;
    return true;
}

bool HDiagramWidget::drawGrid(QPainter *)
{
    if (!isDrawGrid() || !d_ptr->plotArea.isValid())
        return false;
    return true;
}

bool HDiagramWidget::drawPolygon(QPainter *)
{
    if (!d_ptr->plotArea.isValid())
        return false;
    return true;
}

bool HDiagramWidget::drawElse(QPainter *)
{
    return true;
}

void HDiagramWidget::resizeEvent(QResizeEvent *e)
{
    setPlotArea(d_ptr->calcPlotArea(e->size()));
    refreshPixmap();
}

void HDiagramWidget::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, d_ptr->pixmap);

    if (hasFocus())
    {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, &painter, this);
    }
}

void HDiagramWidget::init()
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::NoFocus);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}
