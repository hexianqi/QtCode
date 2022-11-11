#include "HHoverShowWidget_p.h"

HE_BEGIN_NAMESPACE

HHoverShowWidget::HHoverShowWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HHoverShowWidgetPrivate)
{
}

HHoverShowWidget::HHoverShowWidget(HHoverShowWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HHoverShowWidget::~HHoverShowWidget()
{
}

HE_END_NAMESPACE

#include "generalcontrol_hovershowmsg_widget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QDesktopWidget>
#include <QApplication>
#include "common/common.h"



void generalControl_hoverShowMSG_Widget::setInfoText(const QString & text)
{
    textLabel->setText(text);
    timer.start();
    show();
    adjustSize();

    move((QApplication::desktop()->width() - this->width()) / 2,(QApplication::desktop()->height() - this->height()) * 0.25);
}

void generalControl_hoverShowMSG_Widget::set_style()
{
    if(currentThemeIndex < 11)
    {
        setWindowOpacity(0.8);
        frame->setStyleSheet(QString("QFrame#frame{background-color:#%1;border-radius:10px;}").arg(style_main_color));
    }
    else
    {
        setWindowOpacity(1);
        frame->setStyleSheet(QString("QFrame#frame{background-color:#%1;border-radius:10px;}").arg(lineEdit_and_combox_Bg));
    }
}

QSize generalControl_hoverShowMSG_Widget::sizeHint() const
{
    auto fontMetics = this->fontMetrics();
    auto size = fontMetics.size(Qt::AlignCenter,textLabel->text());
    return size;
}

generalControl_hoverShowMSG_Widget::generalControl_hoverShowMSG_Widget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::ToolTip);

    setWindowOpacity(0.8);

    textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setStyleSheet("color:#FFFFFF;");

    auto hb = new QHBoxLayout;
    hb->addWidget(textLabel);
    frame = new QFrame(this);
    frame->setObjectName("frame");
    frame->setLayout(hb);
    hb->setMargin(10);

    hb = new QHBoxLayout;
    hb->addWidget(frame);

    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);
    effect->setColor(QColor("#444444"));
    effect->setBlurRadius(10);
    frame->setGraphicsEffect(effect);
    hb->setMargin(10);

    setLayout(hb);

    connect(&timer,&QTimer::timeout,this,&generalControl_hoverShowMSG_Widget::close);
    timer.setSingleShot(true);
    timer.setInterval(3000);

    auto font = this->font();
    font.setPixelSize(30);
    font.setBold(true);
    setFont(font);
}
