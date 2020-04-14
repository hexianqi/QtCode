#include "HHueSatPicker_p.h"
#include "HDrawHelper.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QStyleOptionFrame>

HE_CONTROL_BEGIN_NAMESPACE

HHueSatPicker::HHueSatPicker(QWidget *parent) :
    QFrame(parent),
    d_ptr(new HHueSatPickerPrivate)
{
    init();
}

HHueSatPicker::HHueSatPicker(HHueSatPickerPrivate &p, QWidget *parent) :
    QFrame(parent),
    d_ptr(&p)
{
    init();
}

HHueSatPicker::~HHueSatPicker() = default;

QSize HHueSatPicker::sizeHint() const
{
    return {(d_ptr->maximumHue - d_ptr->minimumHue) + 2 * frameWidth(), (d_ptr->maximumSat - d_ptr->minimumSat) + 2 * frameWidth()};
}

QSize HHueSatPicker::minimumSizeHint() const
{
    return {qMin((d_ptr->maximumHue - d_ptr->minimumHue) / 4, 40) + 2 * frameWidth(), qMin((d_ptr->maximumSat - d_ptr->minimumSat) / 4, 40) + 2 * frameWidth()};
}

int HHueSatPicker::minimumHue() const
{
    return d_ptr->minimumHue;
}

int HHueSatPicker::maximumHue() const
{
    return d_ptr->maximumHue;
}

int HHueSatPicker::minimumSat() const
{
    return d_ptr->minimumSat;
}

int HHueSatPicker::maximumSat() const
{
    return d_ptr->maximumSat;
}

int HHueSatPicker::value() const
{
    return d_ptr->value;
}

QColor HHueSatPicker::color() const
{
    return d_ptr->color;
}

void HHueSatPicker::setHueRange(int minimum, int maximum)
{
    if (minimum < 0 || maximum < 0 || minimum > 359 || maximum > 359)
        return;
    if (minimum >= maximum)
        qSwap(minimum, maximum);

    d_ptr->minimumHue = minimum;
    d_ptr->maximumHue = maximum;
    emit hueChanged(minimum, maximum);
    updateGeometry();
    buildPixmap();
    update();
}

void HHueSatPicker::setSatRange(int minimum, int maximum)
{
    if (minimum < 0 || maximum < 0 || minimum > 255 || maximum > 255)
        return;
    if (minimum >= maximum)
        qSwap(minimum, maximum);

    d_ptr->minimumSat = minimum;
    d_ptr->maximumSat = maximum;
    emit satChanged(minimum, maximum);
    updateGeometry();
    buildPixmap();
    update();
}

void HHueSatPicker::setMinimumHue(int value)
{
    setHueRange(value, d_ptr->maximumHue);
}

void HHueSatPicker::setMaximumHue(int value)
{
    setHueRange(d_ptr->minimumHue, value);
}

void HHueSatPicker::setMinimumSat(int value)
{
    setSatRange(value, d_ptr->maximumSat);
}

void HHueSatPicker::setMaximumSat(int value)
{
    setSatRange(d_ptr->minimumSat, value);
}

void HHueSatPicker::setValue(int value)
{
    if (d_ptr->value == value || value < 0 || value > 255)
        return;

    d_ptr->value = value;
    emit valueChanged(value);
    buildPixmap();
    update();
}

void HHueSatPicker::setColor(const QColor &value)
{
    if (d_ptr->color == value)
        return;

    int h, s, v;
    value.getHsv(&h, &s, &v);
    if (d_ptr->value != v)
        setValue(v);
    if (h < d_ptr->minimumHue || h > d_ptr->maximumHue)
    {
        int span = d_ptr->maximumHue - d_ptr->minimumHue;
        int hh = qMax(0, h - span / 2);
        setHueRange(hh, hh + span);
    }
    if (s < d_ptr->minimumSat || s > d_ptr->maximumSat)
    {
        int span = d_ptr->maximumSat - d_ptr->minimumSat;
        int ss = qMax(0, s - span / 2);
        setSatRange(ss, ss + span);
    }
    d_ptr->point = QPointF(hueToX(h), satToY(s));
    d_ptr->color = value;
    emit colorPicked(value);
    update();
}

void HHueSatPicker::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        colorPick(e->localPos());
    QFrame::mousePressEvent(e);
}

void HHueSatPicker::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
        colorPick(e->localPos());
    QFrame::mouseMoveEvent(e);
}

void HHueSatPicker::resizeEvent(QResizeEvent *e)
{
    QFrame::resizeEvent(e);
    buildPixmap();
    update();
}

void HHueSatPicker::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawFrame(&painter);
    QStyleOptionFrame option;
    option.initFrom(this);
    if (option.state & QStyle::State_Enabled)
    {
        painter.drawPixmap(contentsRect().topLeft(), d_ptr->pixmap);
        HDrawHelper::drawCrosshair(&painter, d_ptr->point, 3, Qt::black);
    }
    else
    {
        QIcon icon(d_ptr->pixmap);
        icon.paint(&painter, contentsRect(), Qt::AlignCenter, QIcon::Disabled);
    }
}

void HHueSatPicker::init()
{
    setWindowIcon(QIcon(":/image/ww/huesatpicker.png"));
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void HHueSatPicker::buildPixmap()
{
    int cy = contentsRect().height();
    int cx = contentsRect().width();
    auto image = QImage(cx, cy, QImage::Format_ARGB32);
    for (int y = 0; y < cy; y++)
    {
        for (int x = 0; x < cx; x++)
            image.setPixel(x, y, QColor::fromHsvF(hueFromX(x), satFromY(y), d_ptr->value / 255.0).rgb());
    }
    d_ptr->pixmap = QPixmap::fromImage(image);
}

double HHueSatPicker::hueFromX(double value) const
{
    return (d_ptr->maximumHue - value * (d_ptr->maximumHue - d_ptr->minimumHue) / contentsRect().width()) / 359.0;
}

double HHueSatPicker::hueToX(double value) const
{
    return contentsRect().width() * (1.0 - value / (d_ptr->maximumHue - d_ptr->minimumHue));
}

double HHueSatPicker::satFromY(double value) const
{
    return (d_ptr->maximumSat - value * (d_ptr->maximumSat - d_ptr->minimumSat) / contentsRect().height()) / 255.0;
}

double HHueSatPicker::satToY(double value) const
{
    return contentsRect().height() * (1.0 - value / (d_ptr->maximumSat - d_ptr->minimumSat));
}

void HHueSatPicker::colorPick(const QPointF &point)
{
    if (!contentsRect().contains(point.toPoint()))
        return;
    auto h = hueFromX(point.x() - contentsRect().x());
    auto s = satFromY(point.y() - contentsRect().y());
    auto v = d_ptr->value / 255.0;
    if (h < 0.0 || h > 1.0 || s < 0.0 || s > 1.0)
        return;
    emit colorPicked(QColor::fromHsvF(h, s, v));
    d_ptr->point = point;
    update();
}

HE_CONTROL_END_NAMESPACE
