#include "HCie1931Widget_p.h"
#include "HCartesianCoordinate.h"
#include "HPluginHelper.h"
#include "HPainterHelper.h"
#include "HPositionTracking.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QAction>
#include <QtWidgets/QLabel>

HCie1931WidgetPrivate::HCie1931WidgetPrivate()
{
    square = true;
    fontPointFocus.setPointSize(12);
    fontPointFocus.setWeight(QFont::Bold);
    cie1931.load(":/image/CIE1931.png");
    readStandard();
}

void HCie1931WidgetPrivate::readStandard()
{
    int i,n;
    double x,y;
    QString str;

    QFile file(":/dat/Chromaticity.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        horseshoe.append(QPointF(x,y));
    }
    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        planckian.append(QPointF(x,y));
    }
}

HCie1931Widget::HCie1931Widget(QWidget *parent) :
    HCartesianWidget(*new HCie1931WidgetPrivate, parent)
{
    init();
}

void HCie1931Widget::setEnableTracking(bool b)
{
    Q_D(HCie1931Widget);
    d->tracking->setEnable(b);
    d->label->setVisible(b);
}

void HCie1931Widget::setDrawCIE(bool b)
{
    Q_D(HCie1931Widget);
    if (d->drawCIE == b)
        return;
    d->drawCIE = b;
    refreshPixmap();
}

void HCie1931Widget::setDrawHorseshoe(bool b)
{
    Q_D(HCie1931Widget);
    if (d->drawHorseshoe == b)
        return;
    d->drawHorseshoe = b;
    refreshPixmap();
}

void HCie1931Widget::setDrawPlanckian(bool b)
{
    Q_D(HCie1931Widget);
    if (d->drawPlanckian == b)
        return;
    d->drawPlanckian = b;
    refreshPixmap();
}

void HCie1931Widget::setDrawGrade(bool b)
{
    Q_D(HCie1931Widget);
    if (d->drawGrade == b)
        return;
    d->drawGrade = b;
    refreshPixmap();
}

void HCie1931Widget::setDrawPoint(bool b)
{
    Q_D(HCie1931Widget);
    if (d->drawPoint == b)
        return;
    d->drawPoint = b;
    refreshPixmap();
}

void HCie1931Widget::setColorHorseshoe(const QColor &value)
{
    Q_D(HCie1931Widget);
    if (d->colorHorseshoe == value)
        return;
    d->colorHorseshoe = value;
    refreshPixmap();
}

void HCie1931Widget::setColorPlanckian(const QColor &value)
{
    Q_D(HCie1931Widget);
    if (d->colorPlanckian == value)
        return;
    d->colorPlanckian = value;
    refreshPixmap();
}

void HCie1931Widget::setColorGrade(const QColor &value)
{
    Q_D(HCie1931Widget);
    if (d->colorGrade == value)
        return;
    d->colorGrade = value;
    refreshPixmap();
}

void HCie1931Widget::setColorGradeFocus(const QColor &value)
{
    Q_D(HCie1931Widget);
    if (d->colorGradeFocus == value)
        return;
    d->colorGradeFocus = value;
    refreshPixmap();
}

void HCie1931Widget::setColorPoint(const QColor &value)
{
    Q_D(HCie1931Widget);
    if (d->colorPoint == value)
        return;
    d->colorPoint = value;
    refreshPixmap();
}

void HCie1931Widget::setColorPointFocus(const QColor &value)
{
    Q_D(HCie1931Widget);
    if (d->colorPointFocus == value)
        return;
    d->colorPointFocus = value;
    refreshPixmap();
}

void HCie1931Widget::setFontPointFocus(const QFont &value)
{
    Q_D(HCie1931Widget);
    if (d->fontPointFocus == value)
        return;
    d->fontPointFocus = value;
    refreshPixmap();
}

bool HCie1931Widget::isEnableTracking()
{
    Q_D(HCie1931Widget);
    return d->tracking->isEnable();
}

bool HCie1931Widget::isDrawCIE()
{
    Q_D(HCie1931Widget);
    return d->drawCIE;
}

bool HCie1931Widget::isDrawHorseshoe()
{
    Q_D(HCie1931Widget);
    return d->drawHorseshoe;
}

bool HCie1931Widget::isDrawPlanckian()
{
    Q_D(HCie1931Widget);
    return d->drawPlanckian;
}

bool HCie1931Widget::isDrawGrade()
{
    Q_D(HCie1931Widget);
    return d->drawGrade;
}

bool HCie1931Widget::isDrawPoint()
{
    Q_D(HCie1931Widget);
    return d->drawPoint;
}

QColor HCie1931Widget::colorHorseshoe()
{
    Q_D(HCie1931Widget);
    return d->colorHorseshoe;
}

QColor HCie1931Widget::colorPlanckian()
{
    Q_D(HCie1931Widget);
    return d->colorPlanckian;
}

QColor HCie1931Widget::colorGrade()
{
    Q_D(HCie1931Widget);
    return d->colorGrade;
}

QColor HCie1931Widget::colorGradeFocus()
{
    Q_D(HCie1931Widget);
    return d->colorGradeFocus;
}

QColor HCie1931Widget::colorPoint()
{
    Q_D(HCie1931Widget);
    return d->colorPoint;
}

QColor HCie1931Widget::colorPointFocus()
{
    Q_D(HCie1931Widget);
    return d->colorPointFocus;
}

QFont HCie1931Widget::fontPointFocus()
{
    Q_D(HCie1931Widget);
    return d->fontPointFocus;
}

void HCie1931Widget::setGradeFocus(const QPolygonF &value)
{
    Q_D(HCie1931Widget);
    d->gradeFocus = value;
    refreshPixmap();
}

void HCie1931Widget::setGrade(const QList<QPolygonF> &value)
{
    Q_D(HCie1931Widget);
    d->grades = value;
    refreshPixmap();
}

void HCie1931Widget::addGrade(const QPolygonF &value, bool focus, bool refresh)
{
    Q_D(HCie1931Widget);
    d->grades << value;
    if (focus)
        d->gradeFocus = value;
    if (refresh)
        refreshPixmap();
}

void HCie1931Widget::removeGrade(const QPolygonF &value, bool refresh)
{
    Q_D(HCie1931Widget);
    if (d->grades.removeAll(value) > 0 && refresh)
        refreshPixmap();
}

void HCie1931Widget::clearGrade()
{
    Q_D(HCie1931Widget);
    d->grades.clear();
    d->gradeFocus.clear();
    refreshPixmap();
}

void HCie1931Widget::setPointFocus(QPointF value)
{
    Q_D(HCie1931Widget);
    d->pointFocus = value;
    refreshPixmap();
}

void HCie1931Widget::setPoint(const QList<QPointF> &value)
{
    Q_D(HCie1931Widget);
    d->points = value;
    refreshPixmap();
}

void HCie1931Widget::addPoint(QPointF value, bool focus, bool refresh)
{
    Q_D(HCie1931Widget);
    d->points << value;
    if (focus)
        d->pointFocus = value;
    if (refresh)
        refreshPixmap();
}

void HCie1931Widget::clearPoint()
{
    Q_D(HCie1931Widget);
    d->points.clear();
    d->pointFocus = QPointF();
    refreshPixmap();
}

void HCie1931Widget::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCie1931Widget);
    d->tracking->mouseMoveEvent(e);
    HCartesianWidget::mouseMoveEvent(e);
}

void HCie1931Widget::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_D(HCie1931Widget);
    if (isEnableTracking())
        emit mouseDoubleClicked(d->coordinate->mapToValue(e->localPos(), d->plotArea));
    HCartesianWidget::mouseDoubleClickEvent(e);
}

bool HCie1931Widget::drawElse(QPainter *painter)
{
    HCartesianWidget::drawElse(painter);
    drawCIE(painter);
    drawHorseshoe(painter);
    drawPlanckian(painter);
    drawGradeBlock(painter);
    drawPoint(painter);
    return true;
}

bool HCie1931Widget::drawCIE(QPainter *painter)
{
    Q_D(HCie1931Widget);
    if (!isDrawCIE() || !isValid())
        return false;

    auto target = d->plotArea.adjusted(1, 1, -1, -1);
    auto source = d->coordinate->mapToAxis(d->cie1931.rect(), QRectF(0, 0, 1, 1));
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->drawPixmap(target, d->cie1931, source);
    painter->restore();
    return true;
}

bool HCie1931Widget::drawHorseshoe(QPainter *painter)
{
    Q_D(HCie1931Widget);
    if (!isDrawHorseshoe() || !isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(d->colorHorseshoe);
    painter->setBrush(Qt::NoBrush);
    painter->drawPolygon(d->coordinate->mapToPosition(d->horseshoe, d->plotArea));
    painter->restore();
    return true;
}

bool HCie1931Widget::drawPlanckian(QPainter *painter)
{
    Q_D(HCie1931Widget);
    if (!isDrawPlanckian() || !isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QPen(d->colorPlanckian, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawPolyline(d->coordinate->mapToPosition(d->planckian, d->plotArea));
    painter->restore();
    return true;
}

bool HCie1931Widget::drawGradeBlock(QPainter *painter)
{
    Q_D(HCie1931Widget);
    if (!isDrawGrade() || !isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(d->colorGrade);
    for (const auto &p : d->grades)
        painter->drawPolygon(d->coordinate->mapToPosition(p, d->plotArea));

    painter->setPen(QPen(d->colorGradeFocus, 2));
    painter->drawPolygon(d->coordinate->mapToPosition(d->gradeFocus, d->plotArea));
    painter->restore();
    return true;
}

bool HCie1931Widget::drawPoint(QPainter *painter)
{
    Q_D(HCie1931Widget);
    if (!isDrawPoint() || !isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(d->colorPoint);
    for (auto p : d->points)
        HPainterHelper::drawCrossCursor(painter, d->coordinate->mapToPosition(p, d->plotArea));
    if (!d->pointFocus.isNull())
    {
        auto text = QString("%1, %2").arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4);
        painter->setPen(QPen(d->colorPointFocus, 2));
        HPainterHelper::drawCrossCursor(painter, d->coordinate->mapToPosition(d->pointFocus, d->plotArea));
        painter->setFont(d->fontPointFocus);
        painter->drawText(d->plotArea.adjusted(10, 10, -10, -10), Qt::AlignRight | Qt::AlignTop, text);
    }
    painter->restore();
    return true;
}

void HCie1931Widget::handlePlotAreaChanged(QRectF value)
{
    Q_D(HCie1931Widget);
    d->tracking->setValidRegion(value);
    d->label->setGeometry(value.left() + 10, value.top() - 20, value.width() - 20, fontMetrics().height());
}

void HCie1931Widget::handlePositionChanged(QPointF pos)
{
    Q_D(HCie1931Widget);
    auto p = d->coordinate->mapToValue(pos, d->plotArea);
    d->label->setText(QString("%1, %2").arg(p.x(), 0, 'f', 4).arg(p.y(), 0, 'f', 4));
}

void HCie1931Widget::init()
{
    Q_D(HCie1931Widget);
    auto f = font();
    f.setPointSize(10);
    d->tracking = new HPositionTracking(this);
    d->label = new QLabel(this);
    d->label->setFont(f);
    auto enableCIE = new QAction(tr("色品图(&E)"));
    enableCIE->setCheckable(true);
    enableCIE->setChecked(isDrawCIE());
    auto enableHorseshoe = new QAction(tr("马蹄线(&H)"));
    enableHorseshoe->setCheckable(true);
    enableHorseshoe->setChecked(isDrawHorseshoe());
    auto enablePlanckian = new QAction(tr("黑体轨迹(&P)"));
    enablePlanckian->setCheckable(true);
    enablePlanckian->setChecked(isDrawPlanckian());
    auto enableGrade = new QAction(tr("分级区域(&S)"));
    enableGrade->setCheckable(true);
    enableGrade->setChecked(isDrawGrade());
    auto enablePoint = new QAction(tr("打点记录(&O)"));
    enablePoint->setCheckable(true);
    enablePoint->setChecked(isDrawPoint());
    auto clearPoint = new QAction(tr("清除打点记录(&C)"));
    HPluginHelper::addSeparator(this);
    addAction(enableCIE);
    addAction(enableHorseshoe);
    addAction(enablePlanckian);
    addAction(enableGrade);
    HPluginHelper::addSeparator(this);
    addAction(enablePoint);
    addAction(clearPoint);

    connect(this, &HCie1931Widget::plotAreaChanged, this, &HCie1931Widget::handlePlotAreaChanged);
    connect(d->tracking, &HPositionTracking::positionChanged, this, &HCie1931Widget::handlePositionChanged);
    connect(enableCIE, &QAction::toggled, this, &HCie1931Widget::setDrawCIE);
    connect(enableHorseshoe, &QAction::toggled, this, &HCie1931Widget::setDrawHorseshoe);
    connect(enablePlanckian, &QAction::toggled, this, &HCie1931Widget::setDrawPlanckian);
    connect(enableGrade, &QAction::toggled, this, &HCie1931Widget::setDrawGrade);
    connect(enablePoint, &QAction::toggled, this, &HCie1931Widget::setDrawPoint);
    connect(clearPoint, &QAction::triggered, this, &HCie1931Widget::clearPoint);

    setMargins(30, 30, 30, 30);
    setCoordinate(QRectF(0, 0, 0.75, 0.85), 5, 5);
    setWindowIcon(QIcon(":/image/CIE1931_s.png"));
    setWindowTitle(tr("色品图-CIE1931"));
}
