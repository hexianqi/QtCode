#include "HRoundShadowWidget_p.h"
#include <QtGui/QtEvents>
#include <QtWidgets/QLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>

HE_BEGIN_NAMESPACE

HRoundShadowWidget::HRoundShadowWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HRoundShadowWidgetPrivate)
{
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(d_ptr->padding);

    d_ptr->widget = new QWidget;
    d_ptr->widget->setObjectName("centerWidget");
    d_ptr->widget->setStyleSheet("QWidget#centerWidget{background-color:#FFFFFF;border-radius:15px;}");
    d_ptr->widget->setGraphicsEffect(shadow);
    d_ptr->widget->setMouseTracking(true);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(d_ptr->widget);
    layout->setContentsMargins(d_ptr->padding, d_ptr->padding, d_ptr->padding, d_ptr->padding);

    setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

HRoundShadowWidget::~HRoundShadowWidget()
{
}

void HRoundShadowWidget::setCenterWidgetLayout(QLayout *layout)
{
    if (d_ptr->widget->layout())
        return;

    int left{0},top{0},right{0},bottom{0};
    layout->getContentsMargins(&left, &top, &right, &bottom);
    layout->setContentsMargins(std::max(left, d_ptr->padding),std::max(top, d_ptr->padding), std::max(right, d_ptr->padding),std::max(bottom, d_ptr->padding));
    d_ptr->widget->setLayout(layout);
}

void HRoundShadowWidget::mousePressEvent(QMouseEvent *event)
{
    d_ptr->lastGeometry = geometry();
    d_ptr->lastPos = event->pos();
    if (d_ptr->rectRight.contains(d_ptr->lastPos))
        d_ptr->mousePressType = PressedRight;
    else if (d_ptr->rectBottom.contains(d_ptr->lastPos))
        d_ptr->mousePressType = PressedBottom;
    else if (d_ptr->rectRightBottom.contains(d_ptr->lastPos))
        d_ptr->mousePressType = PressedRightBottom;
    else
        d_ptr->mousePressType = PressedNotInPadding;
    QWidget::mousePressEvent(event);
}

void HRoundShadowWidget::mouseReleaseEvent(QMouseEvent *event)
{
    d_ptr->mousePressType = NoPressed;
    setCursor(Qt::ArrowCursor);
    updatePaddingRect();
    QWidget::mouseReleaseEvent(event);
}

void HRoundShadowWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto point = event->pos();
    if (d_ptr->resizeEnable)
    {
        updatePaddingRect();
        if (d_ptr->rectRight.contains(point))
            setCursor(Qt::SizeHorCursor);
        else if (d_ptr->rectBottom.contains(point))
            setCursor(Qt::SizeVerCursor);
        else if (d_ptr->rectRightBottom.contains(point))
            setCursor(Qt::SizeFDiagCursor);
        else
            setCursor(Qt::ArrowCursor);
    }

    // 根据当前鼠标位置,计算XY轴移动了多少
    auto offsetX = point.x() - d_ptr->lastPos.x();
    auto offsetY = point.y() - d_ptr->lastPos.y();

    // 根据按下处的位置判断是否是移动控件还是拉伸控件
    if (d_ptr->moveEnable && d_ptr->mousePressType == PressedNotInPadding)
        move(x() + offsetX, y() + offsetY);


    if (d_ptr->resizeEnable)
    {
        if (d_ptr->mousePressType == PressedRight)
            setGeometry(d_ptr->lastGeometry.x(), d_ptr->lastGeometry.y(), d_ptr->lastGeometry.width() + offsetX, d_ptr->lastGeometry.height());
        else if (d_ptr->mousePressType == PressedBottom)
            setGeometry(d_ptr->lastGeometry.x(), d_ptr->lastGeometry.y(), d_ptr->lastGeometry.width(), d_ptr->lastGeometry.height() + offsetY);
        else if (d_ptr->mousePressType == PressedRightBottom)
            setGeometry(x(), y(), d_ptr->lastGeometry.width() + offsetX, d_ptr->lastGeometry.height() + offsetX);
        updatePaddingRect();
    }
    QWidget::mouseMoveEvent(event);
}

void HRoundShadowWidget::updatePaddingRect()
{
    int padding = 20;
    d_ptr->rectRight = QRect(width() - padding, padding, padding, height() - padding * 2);
    d_ptr->rectBottom = QRect(padding, height() - padding, width() - padding * 2, padding);
    d_ptr->rectRightBottom = QRect(width() - padding, height() - padding, padding, padding);
}

HE_END_NAMESPACE
