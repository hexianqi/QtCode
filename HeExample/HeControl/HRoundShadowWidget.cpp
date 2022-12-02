#include "HRoundShadowWidget_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HRoundShadowWidget::HRoundShadowWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HRoundShadowWidgetPrivate)
{
    d_ptr->widget = new QWidget;
    d_ptr->widget->setObjectName("centerWidget");
    d_ptr->widget->setStyleSheet("QWidget#centerWidget{background-color:#FFFFFF;border-radius:15px;}");

}

HRoundShadowWidget::~HRoundShadowWidget()
{
}

HE_END_NAMESPACE

//#ifndef SHADOW_WIDGET_H
//#define SHADOW_WIDGET_H

//#include <QWidget>

//class Shadow_Widget : public QWidget
//{
//    Q_OBJECT

//public:
//    Shadow_Widget(QWidget *parent = nullptr);
//    ~Shadow_Widget();




//};
//#endif // SHADOW_WIDGET_H

//#include "shadow_widget.h"
//#include <QVBoxLayout>
//#include <QGraphicsDropShadowEffect>
//#include <QEvent>
//#include <QMouseEvent>

//Shadow_Widget::Shadow_Widget(QWidget *parent)
//    : QWidget(parent)
//{

//    QVBoxLayout *lay_bg = new QVBoxLayout;
//    lay_bg->addWidget(widget);

//    setAttribute(Qt::WA_TranslucentBackground, true);
//    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    shadow->setOffset(0, 0);
//    shadow->setColor(QColor("#444444"));
//    shadow->setBlurRadius(padding);
//    widget->setGraphicsEffect(shadow);
//    lay_bg->setContentsMargins(padding,padding,padding,padding);

//    setLayout(lay_bg);
//    setMouseTracking(true);
//    widget->setMouseTracking(true);
//}

//Shadow_Widget::~Shadow_Widget()
//{
//}

//void Shadow_Widget::mouseMoveEvent(QMouseEvent *event)
//{
//    QPoint point = event->pos();
//    if (resizeEnable)
//    {
//        updatePaddingRect();
//        if (rectRight.contains(point))
//        {
//            setCursor(Qt::SizeHorCursor);
//        }
//        else if (rectBottom.contains(point))
//        {
//            setCursor(Qt::SizeVerCursor);
//        }
//        else if (rectRightBottom.contains(point))
//        {
//            setCursor(Qt::SizeFDiagCursor);
//        }
//        else
//        {
//            setCursor(Qt::ArrowCursor);
//        }
//    }

//    //根据当前鼠标位置,计算XY轴移动了多少
//    int offsetX = point.x() - lastPos.x();
//    int offsetY = point.y() - lastPos.y();

//    //根据按下处的位置判断是否是移动控件还是拉伸控件
//    if (moveEnable)
//    {
//        if (mousePressType == pressType::PressedButNotInPadding)
//        {
//            move(x() + offsetX, y() + offsetY);
//        }
//    }

//    if (resizeEnable)
//    {
//        if (mousePressType == pressType::PressedRight)
//        {
//            setGeometry(rectX, rectY, rectW + offsetX, rectH);
//        }
//        else if (mousePressType == pressType::PressedBottom)
//        {
//            setGeometry(rectX, rectY, rectW, rectH + offsetY);
//        }
//        else if (mousePressType == pressType::PressedRightBottom)
//        {
//            int resizeW = rectW + offsetX;
//            int resizeH = rectH + offsetY;
//            setGeometry(x(), y(), resizeW, resizeH);
//        }
//        else
//        {
//        }
//        updatePaddingRect();
//    }

//    QWidget::mouseMoveEvent(event);
//}

//void Shadow_Widget::mousePressEvent(QMouseEvent *event)
//{
//    rectX = x();
//    rectY = y();
//    rectW = width();
//    rectH = height();
//    lastPos = event->pos();

//    if (rectRight.contains(lastPos))
//    {
//        mousePressType = pressType::PressedRight;
//    }
//    else if (rectBottom.contains(lastPos))
//    {
//        mousePressType = pressType::PressedBottom;
//    }
//    else if (rectRightBottom.contains(lastPos))
//    {
//        mousePressType = pressType::PressedRightBottom;
//    }
//    else
//    {
//        mousePressType = pressType::PressedButNotInPadding;
//    }
//    QWidget::mousePressEvent(event);
//}

//void Shadow_Widget::mouseReleaseEvent(QMouseEvent *event)
//{
//    mousePressType = pressType::NoPressed;
//    setCursor(Qt::ArrowCursor);
//    updatePaddingRect();
//    QWidget::mouseReleaseEvent(event);
//}

//void Shadow_Widget::setLayout(QLayout *layout)
//{
//    QWidget::setLayout(layout);
//}

//void Shadow_Widget::setCenterWidgetLayout(QLayout *layout)
//{
//    if(widget->layout())
//        return;

//    int left{0},top{0},right{0},bottom{0};
//    layout->getContentsMargins(&left, &top, &right, &bottom);
//    layout->setContentsMargins(std::max(left,padding),std::max(top,padding),
//                               std::max(right,padding),std::max(bottom,padding));
//    widget->setLayout(layout);
//}

//void Shadow_Widget::updatePaddingRect()
//{
//    int width = this->width();
//    int height = this->height();
//    int padding = 20;

//    rectRight = QRect(width - padding, padding, padding, height - padding * 2);
//    rectBottom = QRect(padding, height - padding, width - padding * 2, padding);
//    rectRightBottom = QRect(width - padding, height - padding, padding, padding);
//}
