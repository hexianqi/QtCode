#include "HHoverShowWidget_p.h"
#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QApplication>

HE_BEGIN_NAMESPACE

HHoverShowWidget::HHoverShowWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HHoverShowWidgetPrivate)
{
    init();
}

HHoverShowWidget::HHoverShowWidget(HHoverShowWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HHoverShowWidget::~HHoverShowWidget()
{
}

QSize HHoverShowWidget::sizeHint() const
{
    return fontMetrics().size(Qt::AlignCenter, d_ptr->textLabel->text());
}

void HHoverShowWidget::setInfoText(const QString &text)
{
    d_ptr->textLabel->setText(text);
    d_ptr->timer->start();
    show();
    adjustSize();
    move((QApplication::desktop()->width() - width()) / 2, (QApplication::desktop()->height() - height()) * 0.25);
}

void HHoverShowWidget::init()
{
    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);
    effect->setColor(QColor("#444444"));
    effect->setBlurRadius(10);
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setSingleShot(true);
    d_ptr->timer->setInterval(3000);

    d_ptr->textLabel = new QLabel;
    d_ptr->textLabel->setAlignment(Qt::AlignCenter);
    d_ptr->textLabel->setStyleSheet("color:#FFFFFF;");
    d_ptr->frame = new QFrame;
    d_ptr->frame->setObjectName("frame");
    d_ptr->frame->setGraphicsEffect(effect);
    auto layout1 = new QHBoxLayout(d_ptr->frame);
    layout1->addWidget(d_ptr->textLabel);
    layout1->setMargin(10);
    auto layout2 = new QHBoxLayout(this);
    layout2->addWidget(d_ptr->frame);
    layout2->setMargin(10);

    connect(d_ptr->timer, &QTimer::timeout, this, &HHoverShowWidget::close);

    auto font = this->font();
    font.setPixelSize(30);
    font.setBold(true);
    setFont(font);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
    setWindowOpacity(0.8);
}

HE_END_NAMESPACE

