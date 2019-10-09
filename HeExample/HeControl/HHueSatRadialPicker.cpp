#include "HHueSatRadialPicker_p.h"
#include "HDrawHelper.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QIcon>

HE_CONTROL_BEGIN_NAMESPACE

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

HHueSatRadialPicker::~HHueSatRadialPicker()
{
}

QSize HHueSatRadialPicker::sizeHint() const
{
    return QSize(202, 202);
}

QSize HHueSatRadialPicker::minimumSizeHint() const
{
    return QSize(202, 202);
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

    auto side = qMin(width(), height());
    auto r = s * (side / 2 - 2) / 255.0;
    auto x = r * qCos(qDegreesToRadians(h * 1.0));
    auto y = r * qSin(qDegreesToRadians(h * 1.0));
    auto c = rect().center();
    d_ptr->point = QPointF(x + c.x(), c.y() - y);
    d_ptr->color = value;
    emit colorPicked(value);
    update();
}

void HHueSatRadialPicker::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        auto p = e->localPos();
        auto r = radius(p);
        auto side = qMin(width(), height());
        if (r >= side / 2)
            return;
        colorPick(p, r);
    }
    else
        QWidget::mousePressEvent(e);
}

void HHueSatRadialPicker::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        auto p = e->localPos();
        auto r = radius(p);
        auto side = qMin(width(), height());
        if (r >= side / 2)
        {
            r = side / 2;
            p = d_ptr->point;
        }
        colorPick(p, r);
    }
    else
        QWidget::mousePressEvent(e);

}

void HHueSatRadialPicker::resizeEvent(QResizeEvent *)
{
    buildPixmap();
    update();
}

void HHueSatRadialPicker::paintEvent(QPaintEvent *)
{
    if (d_ptr->pixmap.isNull())
        buildPixmap();
    QPainter painter(this);
    painter.drawPixmap(0, 0, d_ptr->pixmap);
    HDrawHelper::drawCrosshair(&painter, d_ptr->point, 3, Qt::black);
}

void HHueSatRadialPicker::init()
{
    setWindowIcon(QIcon(":/image/ww/huesatradialpicker.png"));
    buildGradient(d_ptr->value);
}

void HHueSatRadialPicker::buildGradient(int value)
{
    d_ptr->gradient.setStops(QGradientStops());
    for (int i = 0; i < 360; i++)
        d_ptr->gradient.setColorAt(i / 360.0, QColor::fromHsv(i, 255, value));
    d_ptr->gradient.setColorAt(1, QColor::fromHsv(359, 255, value));
}

void HHueSatRadialPicker::buildPixmap()
{
    auto center = rect().center();
    auto radius = qMin(width(), height()) / 2 - 2;

    d_ptr->gradient.setCenter(center);
    auto pm1 = QImage(size(), QImage::Format_ARGB32);
    pm1.fill(Qt::transparent);
    QPainter painter1(&pm1);
    painter1.setRenderHint(QPainter::Antialiasing, true);
    painter1.setBrush(d_ptr->gradient);
    painter1.setPen(palette().color(QPalette::Shadow));
    painter1.drawEllipse(center, radius, radius);
    d_ptr->pixmap = QPixmap::fromImage(pm1);

    auto gradient = QRadialGradient(center, radius, center);
    for (double i = 0; i < 1.0; i += 0.01)
        gradient.setColorAt(i, QColor::fromHsvF(0, 0, 1, 1 - i));
    auto pm2 = QImage(size(), QImage::Format_ARGB32);
    pm2.fill(Qt::transparent);
    QPainter painter2(&pm2);
    painter2.setRenderHint(QPainter::Antialiasing, true);
    painter2.setBrush(gradient);
    painter2.setPen(palette().color(QPalette::Shadow));
    painter2.drawEllipse(center, radius, radius);
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter2.drawPixmap(0, 0, d_ptr->pixmap);
    d_ptr->pixmap = QPixmap::fromImage(pm2);
}

void HHueSatRadialPicker::colorPick(const QPointF &point, double radius)
{
    auto side = qMin(width(), height());
    auto h = hue(point);
    auto s = 2 * radius / side;
    auto v = d_ptr->value / 255.0;
    d_ptr->point = point;
    emit colorPicked(QColor::fromHsvF(h, s, v));
    update();
}

double HHueSatRadialPicker::radius(const QPointF &point)
{
    auto p = point - rect().center();
    return sqrt(p.x() * p.x() + p.y() * p.y());
}

double HHueSatRadialPicker::hue(const QPointF &point)
{
    auto c = rect().center();
    auto x = c.x() - point.x();
    auto y = point.y() - c.y();
    auto h = qRadiansToDegrees(atan(qAbs(y / x)));
    if (x >= 0 && y >= 0)
        h = 180 + h;
    else if (x >= 0 && y < 0)
        h = 180 - h;
    else if (x < 0 && y >= 0)
        h = 360 - h;
    return h / 360.0;
}

HE_CONTROL_END_NAMESPACE
