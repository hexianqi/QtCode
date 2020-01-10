#include "HTwoColorIndicator_p.h"
#include "HColorDrag.h"
#include <QtCore/QMimeData>
#include <QtGui/qevent.h>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleOptionButton>
#include <QtWidgets/QColorDialog>

HE_CONTROL_BEGIN_NAMESPACE

HTwoColorIndicator::HTwoColorIndicator(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTwoColorIndicatorPrivate)
{
    init();
}

HTwoColorIndicator::HTwoColorIndicator(HTwoColorIndicatorPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HTwoColorIndicator::~HTwoColorIndicator()
{
}

QSize HTwoColorIndicator::sizeHint() const
{
    return QSize(50, 50).expandedTo(QApplication::globalStrut() * 1.5);
}

QSize HTwoColorIndicator::minimumSizeHint() const
{
    return QSize(20, 20).expandedTo(QApplication::globalStrut());
}

QColor HTwoColorIndicator::foreground() const
{
    return d_ptr->foreground;
}

QColor HTwoColorIndicator::background() const
{
    return d_ptr->background;
}

bool HTwoColorIndicator::isActive() const
{
    return d_ptr->active;
}

bool HTwoColorIndicator::isDragEnabled() const
{
    return d_ptr->dragEnabled;
}

void HTwoColorIndicator::setForeground(const QColor &value)
{
    if (d_ptr->foreground == value)
        return;
    d_ptr->foreground = value;
    emit foregroundChanged(value);
    update();
}

void HTwoColorIndicator::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    emit backgroundChanged(value);
    update();
}

void HTwoColorIndicator::setActive(bool b)
{
    d_ptr->active = b;
}

void HTwoColorIndicator::setDragEnabled(bool b)
{
    d_ptr->dragEnabled = b;
}

void HTwoColorIndicator::switchColors()
{
    if (d_ptr->foreground == d_ptr->background)
        return;
    qSwap(d_ptr->foreground, d_ptr->background);
    emit foregroundChanged(d_ptr->foreground);
    emit backgroundChanged(d_ptr->background);
    update();
}

void HTwoColorIndicator::mousePressEvent(QMouseEvent *e)
{
    d_ptr->pressPos = e->pos();
    if (e->button() == Qt::LeftButton)
    {
        if (foregroundRect().contains(e->pos()))
        {
            d_ptr->foregroundPress = true;
            d_ptr->backgroundPress = false;
            emit foregroundPressed();
            update();
        }
        else if (backgroundRect().contains(e->pos()))
        {
            d_ptr->foregroundPress = false;
            d_ptr->backgroundPress = true;
            emit backgroundPressed();
            update();
        }
    }
    QWidget::mousePressEvent(e);
}

void HTwoColorIndicator::mouseMoveEvent(QMouseEvent *e)
{
    if (d_ptr->foregroundPress || d_ptr->backgroundPress)
    {
        if (isDragEnabled() && (e->pos() - d_ptr->pressPos).manhattanLength() >= QApplication::startDragDistance())
        {
            auto color = d_ptr->foregroundPress ? foreground() : background();
            auto drag = new HColorDrag(this, color, color.name());
            drag->exec();
            d_ptr->foregroundPress = false;
            d_ptr->backgroundPress = false;
            update();
        }
    }
    else if (testAttribute(Qt::WA_Hover))
        update();
    QWidget::mouseMoveEvent(e);
}

void HTwoColorIndicator::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (d_ptr->foregroundPress && foregroundRect().contains(e->pos()))
        {
            emit foregroundClicked();
            if (isActive())
            {
                auto c = QColorDialog::getColor(foreground(), this, tr("选择前景色"), QColorDialog::ShowAlphaChannel);
                if (c.isValid())
                    setForeground(c);
            }
        }
        else if (d_ptr->backgroundPress && backgroundRect().contains(e->pos()))
        {
            emit backgroundClicked();
            if (isActive())
            {
                auto c = QColorDialog::getColor(background(), this, tr("选择背景色"), QColorDialog::ShowAlphaChannel);
                if (c.isValid())
                    setBackground(c);
            }
        }
        d_ptr->foregroundPress = false;
        d_ptr->backgroundPress = false;
        update();
    }
    QWidget::mouseReleaseEvent(e);
}

void HTwoColorIndicator::dragEnterEvent(QDragEnterEvent *e)
{
    QColor c;
    if (e->mimeData()->hasColor())
        c = e->mimeData()->colorData().value<QColor>();
    else if (e->mimeData()->hasFormat("text/plain"))
        c = QColor(e->mimeData()->text());
    if (c.isValid())
        e->acceptProposedAction();
}

void HTwoColorIndicator::dragMoveEvent(QDragMoveEvent *e)
{
    if (foregroundRect().intersects(e->answerRect()))
    {
        e->acceptProposedAction();
        e->accept(foregroundRect());
    }
    else if (backgroundRect().intersects(e->answerRect()))
    {
        e->acceptProposedAction();
    }
    else e->ignore();
}

void HTwoColorIndicator::dropEvent(QDropEvent *e)
{
    QColor c;
    if (e->mimeData()->hasColor())
        c = e->mimeData()->colorData().value<QColor>();
    else
        c.setNamedColor(e->mimeData()->text());
    if (foregroundRect().contains(e->pos()))
        setForeground(c);
    else if (backgroundRect().contains(e->pos()))
        setBackground(c);
    e->setDropAction(Qt::CopyAction);
}

void HTwoColorIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintSection(&painter, backgroundRect(), d_ptr->background);
    paintSection(&painter, foregroundRect(), d_ptr->foreground);
}

void HTwoColorIndicator::paintSection(QPainter *painter, const QRect &rect, const QColor &color)
{
    QStyleOptionButton option;
    option.initFrom(this);
    option.rect = rect;
    if ((rect.contains(QPoint(3, 3)) && d_ptr->foregroundPress) || (rect.contains(QPoint(width() - 4, height() - 4)) && d_ptr->backgroundPress))
        option.state |= QStyle::State_Sunken;
    else
        option.state |= QStyle::State_Raised;
    if (rect == foregroundRect() && rect.contains(mapFromGlobal(QCursor::pos())))
        option.state |= QStyle::State_MouseOver;
    else if (rect == backgroundRect() && rect.contains(mapFromGlobal(QCursor::pos())) && !foregroundRect().contains(mapFromGlobal(QCursor::pos())))
        option.state |= QStyle::State_MouseOver;
    else
        option.state &= ~(QStyle::State_MouseOver);
    style()->drawControl(QStyle::CE_PushButtonBevel, &option, painter, this);
    auto fillRect = style()->subElementRect(QStyle::SE_PushButtonContents, &option, this);
    auto offset = (option.rect.height() - fillRect.height()) / 2;
    fillRect = option.rect.adjusted(offset, offset, -offset, -offset);
    if (option.state & QStyle::State_Sunken)
        fillRect.translate(style()->pixelMetric(QStyle::PM_ButtonShiftHorizontal), style()->pixelMetric(QStyle::PM_ButtonShiftVertical));
    painter->setPen(Qt::NoPen);
    painter->setBrush(option.state & QStyle::State_Enabled ? color : palette().color(QPalette::Disabled, QPalette::Window ));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(fillRect, 3, 3);
}

QRect HTwoColorIndicator::foregroundRect() const
{
    return QRect(0, 0, width() * 2 / 3, height() * 2 / 3);
}

QRect HTwoColorIndicator::backgroundRect() const
{
    return QRect(width() / 3, height() / 3, width() * 2 / 3, height() * 2 / 3);
}

QRect HTwoColorIndicator::switchButtonRect() const
{
    return QRect(1 + width() / 6, 1 + height() * 4 / 6, width() / 6 - 1, height() / 6 - 1);
}

void HTwoColorIndicator::init()
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setAcceptDrops(true);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

HE_CONTROL_END_NAMESPACE
