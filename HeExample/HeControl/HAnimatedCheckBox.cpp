#include "HAnimatedCheckBox_p.h"
#include <QtCore/QPropertyAnimation>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QStyle>

HE_BEGIN_NAMESPACE

HAnimatedCheckBox::HAnimatedCheckBox(QWidget *parent) :
    QCheckBox(parent),
    d_ptr(new HAnimatedCheckBoxPrivate)
{
    init();
}

HAnimatedCheckBox::HAnimatedCheckBox(HAnimatedCheckBoxPrivate &p, QWidget *parent) :
    QCheckBox(parent),
    d_ptr(&p)
{
    init();
}

HAnimatedCheckBox::~HAnimatedCheckBox() = default;

// 重写 paintEvent 方法，清除 QCheckBox 的默认样式
void HAnimatedCheckBox::paintEvent(QPaintEvent *)
{
}

// 大小改变时调整 indicator 的位置
void HAnimatedCheckBox::resizeEvent(QResizeEvent *)
{
    QStringList qss;
    int b = contentsMargins().left();
    int x = isChecked() ? width() - d_ptr->indicator->width() - b : b;
    int s = height() - b - b;

    d_ptr->indicator->setGeometry(x, b, s, s);
    qss << ".AnimatedCheckBox[checked=true ] { background: #2d8cf0 }"
        << ".AnimatedCheckBox[checked=false] { background: #c5c8ce }"
        << ".AnimatedCheckBoxIndicator { background: white }"
        << QString(".AnimatedCheckBox { border-radius: %1px } .AnimatedCheckBoxIndicator { border-radius: %2px }").arg(height() / 2).arg(d_ptr->indicator->height() / 2);
    setStyleSheet(qss.join("\n"));
    setMinimumWidth(height() * 2);
}

// 点击 AnimatedCheckBox 上的任何地方都切换选中状态，QCheckBox 默认只有点击它的 indicator 或者文字时才进行切换
void HAnimatedCheckBox::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    setChecked(!isChecked());
}

void HAnimatedCheckBox::init()
{
    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(10);
    effect->setOffset(0, 1);
    d_ptr->indicator = new QLabel(this);
    d_ptr->indicator->setProperty("class", "AnimatedCheckBoxIndicator");
    d_ptr->indicator->setGraphicsEffect(effect);
    d_ptr->animation = new QPropertyAnimation(d_ptr->indicator, "pos", this);
    d_ptr->animation->setEasingCurve(QEasingCurve::InOutCubic);
    d_ptr->animation->setDuration(200);

    setMinimumHeight(40);
    setContentsMargins(2, 2, 2, 2);
    setAttribute(Qt::WA_StyledBackground, true);
    setProperty("class", "AnimatedCheckBox");
    connect(this, &QCheckBox::toggled, this, &HAnimatedCheckBox::handleToggled);
}

void HAnimatedCheckBox::handleToggled()
{
    int b = contentsMargins().left();
    int x = isChecked() ? width() - d_ptr->indicator->width() - b : b;

    d_ptr->animation->stop();
    d_ptr->animation->setEndValue(QPoint(x, b));
    d_ptr->animation->start();
    style()->polish(this);
}

HE_END_NAMESPACE
