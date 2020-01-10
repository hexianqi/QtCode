#include "HTaskWidget_p.h"
#include "HTaskHeader.h"
#include "HTaskPanel.h"
#include <QtCore/QEvent>
#include <QtCore/QTimeLine>
#include <QtGui/QPainter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QBoxLayout>

HE_CONTROL_BEGIN_NAMESPACE

HTaskWidget::HTaskWidget(QWidget *body, QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTaskWidgetPrivate)
{
    init(body);
}

HTaskWidget::~HTaskWidget()
{
}

QWidget *HTaskWidget::body() const
{
    return d_ptr->body;
}

void HTaskWidget::setOpen(bool b)
{
    auto button = d_ptr->header->toggleButton();
    if (button->isChecked() != b)
        return;

    button->setChecked(b);
    if (button->arrowType() != Qt::NoArrow)
        button->setArrowType(b ? Qt::UpArrow : Qt::DownArrow);

    auto panel = parent() ? qobject_cast<HTaskPanel *>(parent()->parent()->parent()->parent()) : nullptr;
    if (panel == nullptr || !panel->isAnimated())
    {
        d_ptr->body->setVisible(b);
        return;
    }

    if (d_ptr->timeLine->state() != QTimeLine::NotRunning)
    {
        d_ptr->timeLine->setDirection(d_ptr->timeLine->direction() == QTimeLine::Forward ? QTimeLine::Backward : QTimeLine::Forward);
        return;
    }

    d_ptr->animateWidget = new QWidget;
    d_ptr->animateWidget->installEventFilter(this);
    d_ptr->animateWidget->setEnabled(false);
    d_ptr->animateWidget->setAttribute(Qt::WA_NoSystemBackground, true);
    d_ptr->body->ensurePolished();
    auto size = QLayout::closestAcceptableSize(d_ptr->body, d_ptr->body->sizeHint()).expandedTo(QSize(width(), 0));
    d_ptr->body->resize(size);
    d_ptr->body->setAttribute(Qt::WA_WState_ExplicitShowHide, true);
    d_ptr->body->setAttribute(Qt::WA_WState_Hidden, false);
    d_ptr->pixmap = d_ptr->body->grab();
    d_ptr->body->setAttribute(Qt::WA_WState_Hidden, true);
    d_ptr->timeLine->setDirection(b ? QTimeLine::Forward : QTimeLine::Backward);
    d_ptr->timeLine->setFrameRange(0, b ? size.height() : d_ptr->body->height());
    d_ptr->body->hide();
    d_ptr->layout->addWidget(d_ptr->animateWidget);
    d_ptr->animateWidget->show();
    d_ptr->timeLine->start();
}

void HTaskWidget::setName(const QString &value)
{
    d_ptr->header->setName(value);
    d_ptr->body->setWindowTitle(value);
}

void HTaskWidget::setIcon(const QIcon &value)
{
    d_ptr->header->setIcon(value);
    d_ptr->body->setWindowIcon(value);
}

void HTaskWidget::setToggleIcon(const QIcon &value)
{
    d_ptr->header->setToggleIcon(value);
}

bool HTaskWidget::eventFilter(QObject *object, QEvent *event)
{
    if (d_ptr->animateWidget == object && event->type() == QEvent::Paint)
    {
        QPainter painter(d_ptr->animateWidget);
        painter.drawPixmap(d_ptr->animateWidget->rect(), d_ptr->pixmap, d_ptr->pixmap.rect().adjusted(0, d_ptr->pixmap.height() - d_ptr->animateWidget->height(), 0, 0));
        return true;
    }
    return QWidget::eventFilter(object, event);
}

void HTaskWidget::init(QWidget *body)
{
    d_ptr->body = body;
    d_ptr->animateWidget = nullptr;
    d_ptr->header = new HTaskHeader;
    d_ptr->timeLine = new QTimeLine(1200, this);
    d_ptr->timeLine->setUpdateInterval(20);
    d_ptr->timeLine->setCurveShape(QTimeLine::EaseInOutCurve);
    d_ptr->body->setVisible(false);
    d_ptr->layout = new QVBoxLayout(this);
    d_ptr->layout->setMargin(0);
    d_ptr->layout->addWidget(d_ptr->header);
    d_ptr->layout->addWidget(d_ptr->body);
    setIcon(d_ptr->body->windowIcon());
    setName(d_ptr->body->windowTitle());
    connect(d_ptr->header->toggleButton(), &QToolButton::toggled, this, &HTaskWidget::setOpen);
    connect(d_ptr->timeLine, &QTimeLine::frameChanged, this, &HTaskWidget::animate);
    connect(d_ptr->timeLine, &QTimeLine::finished, this, &HTaskWidget::animateFinished);
}

void HTaskWidget::animate(int value)
{
    d_ptr->animateWidget->setFixedSize(d_ptr->animateWidget->width(), value);
    d_ptr->animateWidget->updateGeometry();
}

void HTaskWidget::animateFinished()
{
    if (d_ptr->timeLine->currentFrame() != 0)
        d_ptr->body->show();
    d_ptr->animateWidget->lower();
    d_ptr->animateWidget->hide();
    d_ptr->animateWidget->deleteLater();
    d_ptr->animateWidget = nullptr;
    d_ptr->header->update();
    updateGeometry();
}

HE_CONTROL_END_NAMESPACE
