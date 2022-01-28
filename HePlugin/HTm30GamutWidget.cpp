#include "HTm30GamutWidget_p.h"
#include "HCartesianCoordinate.h"
#include "HPainterHelper.h"
#include <QtCore/QtMath>
#include <QtCore/QVariant>
#include <QtGui/QPainter>

HTm30GamutWidgetPrivate::HTm30GamutWidgetPrivate()
{
    square = true;
    drawGrid = false;
    cvg.load(":/image/Gamut_background_s.png");
}

HTm30GamutWidget::HTm30GamutWidget(QWidget *parent) :
    HCartesianWidget(*new HTm30GamutWidgetPrivate, parent)
{
    init();
}

HTm30GamutWidget::~HTm30GamutWidget()
{
}

QStringList HTm30GamutWidget::dataType()
{
    return QStringList() << "[TM30_hj_at]" << "[TM30_hj_bt]" << "[TM30_hj_ar]" << "[TM30_hj_br]";
}

void HTm30GamutWidget::setData(const QVariantMap &value)
{
    Q_D(HTm30GamutWidget);
    if (value.contains("[TM30_hj_at]") && value.contains("[TM30_hj_bt]"))
    {
        auto a = value.value("[TM30_hj_at]").value<QList<double>>();
        auto b = value.value("[TM30_hj_bt]").value<QList<double>>();
        for (int i = 0; i < 16 && i < a.size() && i < b.size(); i++)
        {
            d->polyTest[i].setX(a[i]);
            d->polyTest[i].setY(b[i]);
        }
    }
    if (value.contains("[TM30_hj_ar]") &&  value.contains("[TM30_hj_br]"))
    {
        auto a = value.value("[TM30_hj_ar]").value<QList<double>>();
        auto b = value.value("[TM30_hj_br]").value<QList<double>>();
        for (int i = 0; i < 16 && i < a.size() && i < b.size(); i++)
        {
            d->polyReference[i].setX(a[i]);
            d->polyReference[i].setY(b[i]);
        }
    }
    refreshPixmap();
}

bool HTm30GamutWidget::isDrawBackground() const
{
    return true;
}

bool HTm30GamutWidget::isDrawEdge() const
{
    return true;
}

bool HTm30GamutWidget::isDrawHueBin() const
{
    return true;
}

bool HTm30GamutWidget::isDrawVector() const
{
    return true;
}

bool HTm30GamutWidget::drawElse(QPainter *painter)
{
    HCartesianWidget::drawElse(painter);
    painter->setRenderHint(QPainter::Antialiasing, true);
    drawBackground(painter);
    drawEdge(painter);
    drawHueBin(painter);
    drawCross(painter);
    drawVector(painter);
    return true;
}

bool HTm30GamutWidget::drawBackground(QPainter *painter)
{
    Q_D(HTm30GamutWidget);
    if (!isDrawBackground() || !isValid())
        return false;

    auto target = d->plotArea.adjusted(1, 1, -1, -1);
    auto source = d->coordinate->mapToAxis(d->cvg.rect(), QRectF(-40, -40, 80, 80));
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->drawImage(target, d->cvg, source);
    painter->restore();
    return true;
}

bool HTm30GamutWidget::drawEdge(QPainter *painter)
{
    Q_D(HTm30GamutWidget);
    if (!isDrawEdge() || !isValid())
        return false;

    auto pen = QPen(QColor(128, 128, 128), 1, Qt::DashLine);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(pen);
    painter->drawLines(d->coordinate->mapToPosition(d->lineEdge, d->plotArea));
    painter->restore();
    return true;
}

bool HTm30GamutWidget::drawHueBin(QPainter *painter)
{
    Q_D(HTm30GamutWidget);
    if (!isDrawHueBin() || !isValid())
        return false;

    auto f = painter->font();
    f.setPointSize(10);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setFont(f);
    painter->setPen(QColor(64, 64, 64));
    for (int i = 0; i < 16; i++)
        painter->drawText(d->coordinate->mapToPosition(d->rectHueBin[i], d->plotArea), Qt::AlignCenter, QString::number(i + 1));
    painter->restore();
    return true;
}

bool HTm30GamutWidget::drawCross(QPainter *painter)
{
    Q_D(HTm30GamutWidget);
    if (!isValid())
        return false;
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QColor(128, 128, 128));
    HPainterHelper::drawCrossCursor(painter, d->coordinate->mapToPosition(QPointF(0, 0), d->plotArea), 5);
    painter->restore();
    return true;
}

bool HTm30GamutWidget::drawVector(QPainter *painter)
{
    Q_D(HTm30GamutWidget);
    if (!isDrawVector() || !isValid())
        return false;

    auto rect = QRectF(0, 0, 5, 5);
    auto test = d->coordinate->mapToPosition(d->polyTest, d->plotArea);
    auto reference = d->coordinate->mapToPosition(d->polyReference, d->plotArea);

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QPen(Qt::red, 2));
    painter->drawPolygon(test);
    painter->setPen(QPen(Qt::black, 2));
    painter->drawPolygon(reference);
    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(Qt::red);
    for (auto p : test)
    {
        rect.moveCenter(p);
        painter->drawEllipse(rect);
    }
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::black);
    for (auto p : reference)
    {
        rect.moveCenter(p);
        painter->drawRect(rect);
    }
    painter->restore();
    return true;
}

void HTm30GamutWidget::init()
{
    Q_D(HTm30GamutWidget);
    double theta1, theta2;
    for (int i = 0; i < 16; i++)
    {
        QRectF rect(0, 0, 20, 20);
        theta1 = qDegreesToRadians(i * 360 / 16.0);
        theta2 = qDegreesToRadians(i * 360 / 16.0 + 11.25);
        rect.moveCenter(QPointF(35 * cos(theta2), 35 * sin(theta2)));
        d->lineEdge << QLineF(10 * cos(theta1), 10 * sin(theta1), 40 * cos(theta1), 40 * sin(theta1));
        d->rectHueBin << rect;
        d->polyTest << QPointF(15 * cos(theta2), 15 * sin(theta2));
        d->polyReference << QPointF(30 * cos(theta2), 30 * sin(theta2));
    }

    setMargins(35, 35, 35, 35);
    setCoordinate(QRectF(-40, -40, 80, 80), 8, 8);
    setWindowTitle(tr("色域对比图"));
}
