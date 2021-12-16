#include "HNavigationWidget_p.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_BEGIN_NAMESPACE

HNavigationWidget::HNavigationWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HNavigationWidgetPrivate)
{
    init();
}

HNavigationWidget::HNavigationWidget(HNavigationWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HNavigationWidget::~HNavigationWidget() = default;

void HNavigationWidget::addItem(const QString &value)
{
    d_ptr->items.append(value);
}

void HNavigationWidget::setWidth(int value)
{
    setFixedWidth(value);
}

void HNavigationWidget::setRowHeight(int value)
{
    if (d_ptr->rowHeight == value)
        return;
    d_ptr->rowHeight = value;
    update();
}

void HNavigationWidget::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HNavigationWidget::setSelectColor(const QColor &value)
{
    if (d_ptr->selectedColor == value)
        return;
    d_ptr->selectedColor = value;
    update();
}

void HNavigationWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(d_ptr->background);
    painter.drawRect(rect());

    for (int i = 0; i < d_ptr->items.length(); i++)
    {
        auto rect = QRect(0, i * d_ptr->rowHeight, width(), d_ptr->rowHeight);
        QPainterPath itemPath;
        itemPath.addRect(rect);

        if (d_ptr->currentIndex == i)
        {
            painter.setPen("#FFFFFF");
            painter.fillPath(itemPath, d_ptr->selectedColor);
        }
        else
        {
            painter.setPen("#202020");
            painter.fillPath(itemPath, d_ptr->background);
        }
        painter.drawText(rect, Qt::AlignVCenter | Qt::AlignHCenter, d_ptr->items[i]);
    }
}

void HNavigationWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->y() / d_ptr->rowHeight < d_ptr->items.count())
    {
        d_ptr->currentIndex = e->y() / d_ptr->rowHeight;
        emit currentItemChanged(d_ptr->currentIndex);
        update();
    }
}

void HNavigationWidget::init()
{
    setMouseTracking(true);
    setFixedWidth(150);
}

HE_END_NAMESPACE
