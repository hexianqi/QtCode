#include "HHueSatRadialPicker_p.h"
#include "HDrawHelper.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QIcon>

HE_BEGIN_NAMESPACE

HHueSatRadialPicker::HHueSatRadialPicker(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HHueSatRadialPickerPrivate)
{
    init();
}

HHueSatRadialPicker::HHueSatRadialPicker(HHueSatRadialPickerPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HHueSatRadialPicker::~HHueSatRadialPicker() = default;

QSize HHueSatRadialPicker::sizeHint() const
{
    return {202, 202};
}

QSize HHueSatRadialPicker::minimumSizeHint() const
{
    return {202, 202};
}

int HHueSatRadialPicker::heightForWidth(int value) const
{
    return value;
}

int HHueSatRadialPicker::value() const
{
    return d_ptr->value;
}

QColor HHueSatRadialPicker::color() const
{
    return d_ptr->color;
}

void HHueSatRadialPicker::setValue(int value)
{
    if (d_ptr->value == value || value < 0 || value > 255)
        return;

    d_ptr->value = value;
    emit valueChanged(value);
    buildGradient(value);
    buildPixmap();
    update();
}

void HHueSatRadialPicker::setColor(const QColor &value)
{
    if (d_ptr->color == value)
        return;

    int h, s, v;
    value.getHsv(&h, &s, &v);
    if (d_ptr->value != v)
        setValue(v);

    auto x = s * cos(qDegreesToRadians(h * 1.0)) / 255.0;
    auto y = s * sin(qDegreesToRadians(h * 1.0)) / 255.0;
     d_ptr->pos = QPointF(x, -y);
    d_ptr->color = value;
    emit colorPicked(value);
    update();
}

void HHueSatRadialPicker::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        colorPick(event->localPos());
    QWidget::mousePressEvent(event);
}

void HHueSatRadialPicker::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        colorPick(event->localPos());
    QWidget::mouseMoveEvent(event);
}

void HHueSatRadialPicker::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    buildPixmap();
    update();
}

void HHueSatRadialPicker::paintEvent(QPaintEvent *)
{
    if (d_ptr->boardPixmap.isNull())
        buildPixmap();
    QPainter painter(this);
    painter.drawPixmap(0, 0, d_ptr->boardPixmap);
    HDrawHelper::drawCrosshair(&painter, toAbsolute(d_ptr->pos), 3, Qt::black);
}

void HHueSatRadialPicker::init()
{
    setWindowIcon(QIcon(":/Resources/ww/huesatradialpicker.png"));
    buildGradient(d_ptr->value);
}

void HHueSatRadialPicker::buildGradient(int value)
{
    d_ptr->conicalGradient.setStops(QGradientStops());
    for (int i = 0; i < 360; i++)
        d_ptr->conicalGradient.setColorAt(i / 360.0, QColor::fromHsv(i, 255, value));
    d_ptr->conicalGradient.setColorAt(1, QColor::fromHsv(359, 255, value));

    d_ptr->radialGradient.setStops(QGradientStops());
    for (int i = 0; i < 100; i ++)
        d_ptr->radialGradient.setColorAt(i / 100.0, QColor::fromHsvF(0, 0, 1, 1 - i / 100.0));
    d_ptr->radialGradient.setColorAt(1, QColor::fromHsvF(0, 0, 1, 0));
}

void HHueSatRadialPicker::buildPixmap()
{
    d_ptr->boardCenter = rect().center();
    d_ptr->boardRadius = qMin(width(), height()) / 2 - 2;
    d_ptr->conicalGradient.setCenter(d_ptr->boardCenter);
    d_ptr->radialGradient.setCenter(d_ptr->boardCenter);
    d_ptr->radialGradient.setRadius(d_ptr->boardRadius);
    d_ptr->radialGradient.setFocalPoint(d_ptr->boardCenter);

    auto image1 = QImage(size(), QImage::Format_ARGB32);
    image1.fill(Qt::transparent);
    QPainter painter1;
    painter1.begin(&image1);
    painter1.setRenderHint(QPainter::Antialiasing, true);
    painter1.setBrush(d_ptr->conicalGradient);
    painter1.setPen(palette().color(QPalette::Shadow));
    painter1.drawEllipse(d_ptr->boardCenter, d_ptr->boardRadius, d_ptr->boardRadius);
    painter1.end();

    auto image2 = QImage(size(), QImage::Format_ARGB32);
    image2.fill(Qt::transparent);
    QPainter painter2;
    painter2.begin(&image2);
    painter2.setRenderHint(QPainter::Antialiasing, true);
    painter2.setBrush(d_ptr->radialGradient);
    painter2.setPen(palette().color(QPalette::Shadow));
    painter2.drawEllipse(d_ptr->boardCenter, d_ptr->boardRadius, d_ptr->boardRadius);
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter2.drawImage(0, 0, image1);
    painter2.end();
    d_ptr->boardPixmap = QPixmap::fromImage(image2);
}

void HHueSatRadialPicker::colorPick(const QPointF &point)
{
    if (!isInBoard(point))
        return;
    auto r = radius(point);
    auto h = hue(point);
    auto s = r / d_ptr->boardRadius;
    auto v = d_ptr->value / 255.0;
    d_ptr->pos = toRelative(point);
    emit colorPicked(QColor::fromHsvF(h, s, v));
    update();
}

bool HHueSatRadialPicker::isInBoard(const QPointF &point)
{
    return radius(point) <= d_ptr->boardRadius;
}

double HHueSatRadialPicker::radius(const QPointF &point)
{
    auto p = point - d_ptr->boardCenter;
    return sqrt(p.x() * p.x() + p.y() * p.y());
}

double HHueSatRadialPicker::hue(const QPointF &point)
{
    auto x = d_ptr->boardCenter.x() - point.x();
    auto y = point.y() - d_ptr->boardCenter.y();
    auto h = qRadiansToDegrees(atan(qAbs(y / x)));
    if (x >= 0 && y >= 0)
        h = 180 + h;
    else if (x >= 0 && y < 0)
        h = 180 - h;
    else if (x < 0 && y >= 0)
        h = 360 - h;
    return h / 360.0;
}

QPointF HHueSatRadialPicker::toRelative(const QPointF &point)
{
    auto p = point - d_ptr->boardCenter;
    return QPointF(p.x() / d_ptr->boardRadius, p.y() / d_ptr->boardRadius);
}

QPointF HHueSatRadialPicker::toAbsolute(const QPointF &point)
{
    return QPointF(point.x() * d_ptr->boardRadius, point.y() * d_ptr->boardRadius) + d_ptr->boardCenter;
}

HE_END_NAMESPACE
