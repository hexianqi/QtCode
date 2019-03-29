#include "HCIE1931Widget_p.h"
#include "HCartesianCoordinate.h"
#include "HPluginHelper.h"
#include "HPositionTracking.h"
#include <QAction>
#include <QLabel>
#include <QFile>
#include <QIcon>
#include <QMouseEvent>
#include <QPainter>
#include <QTextStream>

HCIE1931WidgetPrivate::HCIE1931WidgetPrivate(HCIE1931Widget *q)
    : HCartesianWidgetPrivate(q)
{
    square = true;
    fontPointFocus.setPointSize(12);
    fontPointFocus.setWeight(QFont::Bold);
    cie1931.load(":/image/CIE1931.png");
    readStandard();
}

void HCIE1931WidgetPrivate::readStandard()
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

HCIE1931Widget::HCIE1931Widget(QWidget *parent)
    : HCartesianWidget(*new HCIE1931WidgetPrivate(this), parent)
{
    init();
}

HCIE1931Widget::HCIE1931Widget(HCIE1931WidgetPrivate &p, QWidget *parent)
    : HCartesianWidget(p, parent)
{
    init();
}

HCIE1931Widget::~HCIE1931Widget()
{
}

void HCIE1931Widget::setEnableTracking(bool b)
{
    Q_D(HCIE1931Widget);
    d->tracking->setEnable(b);
    d->label->setVisible(b);
}

void HCIE1931Widget::setDrawCIE(bool b)
{
    Q_D(HCIE1931Widget);
    if (d->drawCIE == b)
        return;
    d->drawCIE = b;
    refreshPixmap();
}

void HCIE1931Widget::setDrawHorseshoe(bool b)
{
    Q_D(HCIE1931Widget);
    if (d->drawHorseshoe == b)
        return;
    d->drawHorseshoe = b;
    refreshPixmap();
}

void HCIE1931Widget::setDrawPlanckian(bool b)
{
    Q_D(HCIE1931Widget);
    if (d->drawPlanckian == b)
        return;
    d->drawPlanckian = b;
    refreshPixmap();
}

void HCIE1931Widget::setDrawGrade(bool b)
{
    Q_D(HCIE1931Widget);
    if (d->drawGrade == b)
        return;
    d->drawGrade = b;
    refreshPixmap();
}

void HCIE1931Widget::setDrawPoint(bool b)
{
    Q_D(HCIE1931Widget);
    if (d->drawPoint == b)
        return;
    d->drawPoint = b;
    refreshPixmap();
}

void HCIE1931Widget::setColorHorseshoe(QColor value)
{
    Q_D(HCIE1931Widget);
    if (d->colorHorseshoe == value)
        return;
    d->colorHorseshoe = value;
    refreshPixmap();
}

void HCIE1931Widget::setColorPlanckian(QColor value)
{
    Q_D(HCIE1931Widget);
    if (d->colorPlanckian == value)
        return;
    d->colorPlanckian = value;
    refreshPixmap();
}

void HCIE1931Widget::setColorGrade(QColor value)
{
    Q_D(HCIE1931Widget);
    if (d->colorGrade == value)
        return;
    d->colorGrade = value;
    refreshPixmap();
}

void HCIE1931Widget::setColorGradeFocus(QColor value)
{
    Q_D(HCIE1931Widget);
    if (d->colorGradeFocus == value)
        return;
    d->colorGradeFocus = value;
    refreshPixmap();
}

void HCIE1931Widget::setColorPoint(QColor value)
{
    Q_D(HCIE1931Widget);
    if (d->colorPoint == value)
        return;
    d->colorPoint = value;
    refreshPixmap();
}

void HCIE1931Widget::setColorPointFocus(QColor value)
{
    Q_D(HCIE1931Widget);
    if (d->colorPointFocus == value)
        return;
    d->colorPointFocus = value;
    refreshPixmap();
}

void HCIE1931Widget::setFontPointFocus(QFont value)
{
    Q_D(HCIE1931Widget);
    if (d->fontPointFocus == value)
        return;
    d->fontPointFocus = value;
    refreshPixmap();
}

bool HCIE1931Widget::isEnableTracking()
{
    Q_D(HCIE1931Widget);
    return d->tracking->isEnable();
}

bool HCIE1931Widget::isDrawCIE()
{
    Q_D(HCIE1931Widget);
    return d->drawCIE;
}

bool HCIE1931Widget::isDrawHorseshoe()
{
    Q_D(HCIE1931Widget);
    return d->drawHorseshoe;
}

bool HCIE1931Widget::isDrawPlanckian()
{
    Q_D(HCIE1931Widget);
    return d->drawPlanckian;
}

bool HCIE1931Widget::isDrawGrade()
{
    Q_D(HCIE1931Widget);
    return d->drawGrade;
}

bool HCIE1931Widget::isDrawPoint()
{
    Q_D(HCIE1931Widget);
    return d->drawPoint;
}

QColor HCIE1931Widget::colorHorseshoe()
{
    Q_D(HCIE1931Widget);
    return d->colorHorseshoe;
}

QColor HCIE1931Widget::colorPlanckian()
{
    Q_D(HCIE1931Widget);
    return d->colorPlanckian;
}

QColor HCIE1931Widget::colorGrade()
{
    Q_D(HCIE1931Widget);
    return d->colorGrade;
}

QColor HCIE1931Widget::colorGradeFocus()
{
    Q_D(HCIE1931Widget);
    return d->colorGradeFocus;
}

QColor HCIE1931Widget::colorPoint()
{
    Q_D(HCIE1931Widget);
    return d->colorPoint;
}

QColor HCIE1931Widget::colorPointFocus()
{
    Q_D(HCIE1931Widget);
    return d->colorPointFocus;
}

QFont HCIE1931Widget::fontPointFocus()
{
    Q_D(HCIE1931Widget);
    return d->fontPointFocus;
}

void HCIE1931Widget::setGradeFocus(QPolygonF value)
{
    Q_D(HCIE1931Widget);
    d->gradeFocus = value;
    refreshPixmap();
}

void HCIE1931Widget::setGrade(QList<QPolygonF> value)
{
    Q_D(HCIE1931Widget);
    d->grade = value;
    refreshPixmap();
}

void HCIE1931Widget::addGrade(QPolygonF value, bool focus, bool refresh)
{
    Q_D(HCIE1931Widget);
    d->grade << value;
    if (focus)
        d->gradeFocus = value;
    if (refresh)
        refreshPixmap();
}

void HCIE1931Widget::clearGrade()
{
    Q_D(HCIE1931Widget);
    d->grade.clear();
    d->gradeFocus.clear();
    refreshPixmap();
}

void HCIE1931Widget::setPointFocus(QPointF value)
{
    Q_D(HCIE1931Widget);
    d->pointFocus = value;
    refreshPixmap();
}

void HCIE1931Widget::setPoint(QList<QPointF> value)
{
    Q_D(HCIE1931Widget);
    d->point = value;
    refreshPixmap();
}

void HCIE1931Widget::addPoint(QPointF value, bool focus, bool refresh)
{
    Q_D(HCIE1931Widget);
    d->point << value;
    if (focus)
        d->pointFocus = value;
    if (refresh)
        refreshPixmap();
}

void HCIE1931Widget::clearPoint()
{
    Q_D(HCIE1931Widget);
    d->point.clear();
    d->pointFocus = QPointF();
    refreshPixmap();
}

void HCIE1931Widget::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCIE1931Widget);
    d->tracking->mouseMoveEvent(e);
    HCartesianWidget::mouseMoveEvent(e);
}

void HCIE1931Widget::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_D(HCIE1931Widget);
    if (isEnableTracking())
        emit mouseDoubleClicked(d->coordinate->mapToValue(e->localPos(), d->plotArea));
    HCartesianWidget::mouseDoubleClickEvent(e);
}

bool HCIE1931Widget::drawElse(QPainter *painter)
{
    HCartesianWidget::drawElse(painter);
    drawCIE(painter);
    drawHorseshoe(painter);
    drawPlanckian(painter);
    drawGradeBlock(painter);
    drawPoint(painter);
    return true;
}

bool HCIE1931Widget::drawCIE(QPainter *painter)
{
    Q_D(HCIE1931Widget);
    if (!isDrawCIE() || !d->plotArea.isValid())
        return false;

    auto target = d->plotArea.adjusted(1, 1, -1, -1);
    auto source = d->coordinate->mapToAxis(d->cie1931.rect(), QRectF(0, 0, 1, 1));
    painter->drawPixmap(target, d->cie1931, source);
    return true;
}

bool HCIE1931Widget::drawHorseshoe(QPainter *painter)
{
    Q_D(HCIE1931Widget);
    if (!isDrawHorseshoe() || !d->plotArea.isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(d->colorHorseshoe);
    painter->setBrush(Qt::NoBrush);
    painter->drawPolygon(d->coordinate->mapToPosition(d->horseshoe, d->plotArea));
    painter->restore();
    return true;
}

bool HCIE1931Widget::drawPlanckian(QPainter *painter)
{
    Q_D(HCIE1931Widget);
    if (!isDrawPlanckian() || !d->plotArea.isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QPen(d->colorPlanckian, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawPolyline(d->coordinate->mapToPosition(d->planckian, d->plotArea));
    painter->restore();
    return true;
}

bool HCIE1931Widget::drawGradeBlock(QPainter *painter)
{
    Q_D(HCIE1931Widget);
    if (!isDrawGrade() || !d->plotArea.isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(d->colorGrade);
    for (auto p : d->grade)
        painter->drawPolygon(d->coordinate->mapToPosition(p, d->plotArea));

    painter->setPen(QPen(d->colorGradeFocus, 2));
    painter->drawPolygon(d->coordinate->mapToPosition(d->gradeFocus, d->plotArea));
    painter->restore();
    return true;
}

bool HCIE1931Widget::drawPoint(QPainter *painter)
{
    Q_D(HCIE1931Widget);
    if (!isDrawPoint() || !d->plotArea.isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(d->colorPoint);
    for (auto p : d->point)
    {
        auto t = d->coordinate->mapToPosition(p, d->plotArea);
        painter->drawLine(QLineF(t.x(), t.y() - 3, t.x(), t.y() + 3));
        painter->drawLine(QLineF(t.x() - 3, t.y(), t.x() + 3, t.y()));
    }

    if (!d->pointFocus.isNull())
    {
        auto text = QString("(%1, %2)").arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4);
        auto t = d->coordinate->mapToPosition(d->pointFocus, d->plotArea);
        painter->setPen(QPen(d->colorPointFocus, 2));
        painter->drawLine(QLineF(t.x(), t.y() - 3, t.x(), t.y() + 3));
        painter->drawLine(QLineF(t.x() - 3, t.y(), t.x() + 3, t.y()));
        painter->setFont(d->fontPointFocus);
        painter->drawText(d->plotArea.adjusted(10, 10, -10, -10), Qt::AlignRight | Qt::AlignTop, text);
    }
    painter->restore();
    return true;
}

void HCIE1931Widget::handlePlotAreaChanged(QRectF value)
{
    Q_D(HCIE1931Widget);
    d->tracking->setValidRegion(value);
    d->label->setGeometry(value.left() + 10, value.top() + 10, value.width() - 20, fontMetrics().height());
}

void HCIE1931Widget::handlePositionChanged(QPointF pos)
{
    Q_D(HCIE1931Widget);
    auto p = d->coordinate->mapToValue(pos, d->plotArea);
    d->label->setText(QString("(%1, %2)").arg(p.x(), 0, 'f', 4).arg(p.y(), 0, 'f', 4));
}

void HCIE1931Widget::init()
{
    Q_D(HCIE1931Widget);
    d->tracking = new HPositionTracking(this);
    d->label = new QLabel(this);
    d->actionCIE = new QAction(tr("色品图(&E)"));
    d->actionCIE->setCheckable(true);
    d->actionCIE->setChecked(isDrawCIE());
    d->actionHorseshoe = new QAction(tr("马蹄线(&H)"));
    d->actionHorseshoe->setCheckable(true);
    d->actionHorseshoe->setChecked(isDrawHorseshoe());
    d->actionPlanckian = new QAction(tr("黑体轨迹(&P)"));
    d->actionPlanckian->setCheckable(true);
    d->actionPlanckian->setChecked(isDrawPlanckian());
    d->actionGrade = new QAction(tr("分级区域(&S)"));
    d->actionGrade->setCheckable(true);
    d->actionGrade->setChecked(isDrawGrade());
    d->actionPoint = new QAction(tr("打点记录(&O)"));
    d->actionPoint->setCheckable(true);
    d->actionPoint->setChecked(isDrawPoint());
    d->actionClearPoint = new QAction(tr("清除打点记录(&C)"));
    HPluginHelper::addSeparator(this);
    addAction(d->actionCIE);
    addAction(d->actionHorseshoe);
    addAction(d->actionPlanckian);
    addAction(d->actionGrade);
    HPluginHelper::addSeparator(this);
    addAction(d->actionPoint);
    addAction(d->actionClearPoint);

    connect(this, &HCIE1931Widget::plotAreaChanged, this, &HCIE1931Widget::handlePlotAreaChanged);
    connect(d->tracking, &HPositionTracking::positionChanged, this, &HCIE1931Widget::handlePositionChanged);
    connect(d->actionCIE, &QAction::toggled, this, &HCIE1931Widget::setDrawCIE);
    connect(d->actionHorseshoe, &QAction::toggled, this, &HCIE1931Widget::setDrawHorseshoe);
    connect(d->actionPlanckian, &QAction::toggled, this, &HCIE1931Widget::setDrawPlanckian);
    connect(d->actionGrade, &QAction::toggled, this, &HCIE1931Widget::setDrawGrade);
    connect(d->actionPoint, &QAction::toggled, this, &HCIE1931Widget::setDrawPoint);
    connect(d->actionClearPoint, &QAction::triggered, this, &HCIE1931Widget::clearPoint);

    setCoordinate(QRectF(0, 0, 0.75, 0.85), 5, 5);
    setWindowIcon(QIcon(":/image/CIE1931_s.png"));
    setWindowTitle(tr("色品图-CIE1931"));
}
