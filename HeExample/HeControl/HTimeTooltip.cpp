#include "HTimeTooltip_p.h"
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>

HE_CONTROL_BEGIN_NAMESPACE

HTimeTooltip::HTimeTooltip(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTimeTooltipPrivate)
{
    init();
}

HTimeTooltip::HTimeTooltip(HTimeTooltipPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HTimeTooltip::~HTimeTooltip()
{
}

void HTimeTooltip::setTip(const QPoint &pos, const QString &time, const QString &text)
{
    d_ptr->displayedText = time;
    if (!text.isEmpty())
        d_ptr->displayedText.append( " - " ).append(text);

    if (d_ptr->pos != pos || d_ptr->time.length() != time.length() || d_ptr->text != text)
    {
        d_ptr->pos = pos;
        d_ptr->time = time;
        d_ptr->text = text;
        adjustPosition();
    }
    update();
    raise();
}

void HTimeTooltip::show()
{
    setVisible(true);
    raise();
}

void HTimeTooltip::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(qApp->palette().base());
    painter.drawPath(d_ptr->path);
    painter.setFont(d_ptr->font);
    painter.setPen(qApp->palette().text().color());
    painter.drawText(d_ptr->box, Qt::AlignCenter, d_ptr->displayedText);
}

void HTimeTooltip::adjustPosition()
{
    if (d_ptr->displayedText.isEmpty())
    {
        resize(0, 0);
        return;
    }

    // Get the bounding box required to print the text and add some padding
    QFontMetrics metrics(d_ptr->font);
    auto rect = metrics.boundingRect(d_ptr->displayedText);
    rect.adjust(-2, -2, 2, 2);
    rect.moveTo(0, 0 );

    // Resize the widget to fit our needs
    auto screen = QApplication::screenAt(d_ptr->pos)->geometry();
    auto w = rect.width() + 1;
    auto h = rect.height() + d_ptr->tipHeight + 1;
    auto x = d_ptr->pos.x() - w / 2;
    auto y = d_ptr->pos.y() - h * 2 - d_ptr->tipHeight / 2;
    x = qBound(screen.left(), x, screen.left() + screen.width() - w);
    y = qBound(screen.top(), y, screen.top() + screen.height() - h);
    move(x, y);

    auto tipX = d_ptr->pos.x() - x;
    if (d_ptr->box != rect || d_ptr->tipX != tipX )
    {
        d_ptr->box = rect;
        d_ptr->tipX = tipX;
        resize(w, h);
        buildPath();
    }
}

void HTimeTooltip::buildPath()
{
    // Prepare the painter path for future use so
    // we only have to generate the text at runtime.

    auto polygon = QPolygonF()
                   << QPointF(qMax(0, d_ptr->tipX - 3), d_ptr->box.height())
                   << QPointF(d_ptr->tipX, d_ptr->box.height() + d_ptr->tipHeight)
                   << QPointF(qMin(d_ptr->tipX + 3, d_ptr->box.width()), d_ptr->box.height());

    d_ptr->path = QPainterPath();
    d_ptr->path.addRect(d_ptr->box);
    d_ptr->path.addPolygon(polygon);
    // Store the simplified version of the path
    d_ptr->path = d_ptr->path.simplified();
}

void HTimeTooltip::init()
{
    // Inherit from the system default font size -5
    d_ptr->font = QFont("Verdana", qMax(qApp->font().pointSize() - 5, 7));
    d_ptr->tipX = -1;
    setWindowFlags(Qt::ToolTip | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    // Tell Qt that it doesn't need to erase the background before
    // a paintEvent occurs. This should save some CPU cycles.
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    // By default the widget is unintialized and should not be displayed
    resize(0, 0);
}

HE_CONTROL_END_NAMESPACE
