#include "HImageEffectWidget_p.h"
#include "IShaderEffect.h"
#include "HEffectFactory.h"
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>
#include <QtWidgets/QActionGroup>

HE_CONTROL_BEGIN_NAMESPACE

HImageEffectWidget::HImageEffectWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HImageEffectWidgetPrivate)
{
    init();
}

HImageEffectWidget::HImageEffectWidget(HImageEffectWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HImageEffectWidget::~HImageEffectWidget() = default;

QSize HImageEffectWidget::sizeHint() const
{
    return {300, 200};
}

QSize HImageEffectWidget::minimumSizeHint() const
{
    return {60, 40};
}

void HImageEffectWidget::setEffect(IShaderEffect *p)
{
    d_ptr->effect = p;
    startAnimation();
}

double HImageEffectWidget::factor() const
{
    return d_ptr->factor;
}

QString HImageEffectWidget::imageName1() const
{
    return d_ptr->imageName1;
}

QString HImageEffectWidget::imageName2() const
{
    return d_ptr->imageName2;
}

QPixmap HImageEffectWidget::pixmap1() const
{
    return d_ptr->pixmap1;
}

QPixmap HImageEffectWidget::pixmap2() const
{
    return d_ptr->pixmap2;
}

void HImageEffectWidget::setFactor(double value)
{
    if (qFuzzyCompare(d_ptr->factor, value))
        return;
    d_ptr->factor = value;
    update();
}

void HImageEffectWidget::setImageName1(const QString &value)
{
    if (d_ptr->imageName1 == value)
        return;
    d_ptr->imageName1 = value;
    d_ptr->pixmap1 = QPixmap(value);
    update();
}

void HImageEffectWidget::setImageName2(const QString &value)
{
    if (d_ptr->imageName2 == value)
        return;
    d_ptr->imageName2 = value;
    d_ptr->pixmap2 = QPixmap(value);
    update();
}

void HImageEffectWidget::setPixmap1(const QPixmap &value)
{
    if (!d_ptr->pixmap1.isNull() && d_ptr->pixmap1 == value)
        return;
    d_ptr->pixmap1 = value;
    update();
}

void HImageEffectWidget::setPixmap2(const QPixmap &value)
{
    if (!d_ptr->pixmap2.isNull() && d_ptr->pixmap2 == value)
        return;
    d_ptr->pixmap2 = value;
    update();
}

void HImageEffectWidget::startAnimation()
{
    d_ptr->animation->setStartValue(0.0);
    d_ptr->animation->setEndValue(1.0);
    d_ptr->animation->start();
}

void HImageEffectWidget::stopAnimation()
{
    d_ptr->animation->stop();
    setFactor(1.0);
}

void HImageEffectWidget::paintEvent(QPaintEvent *)
{
    if (d_ptr->pixmap1.isNull() || d_ptr->pixmap2.isNull() || d_ptr->effect == nullptr)
        return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    d_ptr->effect->draw(&painter, d_ptr->factor, geometry(), d_ptr->pixmap1);
}

void HImageEffectWidget::changeEffect(QAction *p)
{
    if (p == nullptr)
        return;
    p->setChecked(true);
    auto k = p->data().toString();
    if (!d_ptr->effectCache.contains(k))
        d_ptr->effectCache.insert(k, d_ptr->factory->create(k));
    setEffect(d_ptr->effectCache.value(k));
}

void HImageEffectWidget::init()
{
    setImageName1(":/image/Layout/BorderLayout.png");
    setImageName2(":/image/Layout/CardLayout.png");
    d_ptr->animation = new QPropertyAnimation(this, "factor", this);
    d_ptr->animation->setEasingCurve(QEasingCurve::Linear);
    d_ptr->animation->setDuration(3000);
    d_ptr->factory = new HEffectFactory(this);
    auto group = d_ptr->factory->toActionGroup();
    setContextMenuPolicy(Qt::ActionsContextMenu);
    addActions(group->actions());
    changeEffect(group->actions().at(0));
    connect(group, &QActionGroup::triggered, this, &HImageEffectWidget::changeEffect);
}

HE_CONTROL_END_NAMESPACE
// 下面是2张图片特效，如果图片大小不一致会很怪异
//void ImageAnimation::paintEvent(QPaintEvent *)
//{
//    if (pixmap1.isNull() || pixmap2.isNull()) {
//        return;
//    }

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);

//    switch (animationType) {
//    case 0:
//        fadeEffect(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 1:
//        blindsEffect(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 2:
//        flipRightToLeft(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 3:
//        outsideToInside(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 4:
//        moveLeftToRightEffect(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 5:
//        moveRightToLeftEffect(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 6:
//        moveBottomToUpEffect(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 7:
//        moveUpToBottomEffect(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    case 8:
//        moveBottomToLeftUpEffect(&painter, geometry(), factor, pixmap1, pixmap2);
//        break;
//    default:
//        break;
//    }
//}

//void ImageAnimation::fadeEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
//{
//    int w = rect.width();
//    int h = rect.height();
//    int alpha = 255 * (1.0f - factor);

//    QPixmap alphaPixmap(pixmap1.size());
//    alphaPixmap.fill(Qt::transparent);

//    QPainter p1(&alphaPixmap);
//    p1.setCompositionMode(QPainter::CompositionMode_Source);
//    p1.drawPixmap(0, 0, pixmap1);
//    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
//    p1.fillRect(alphaPixmap.rect(), QColor(0, 0, 0, alpha));
//    p1.end();

//    int x = (w - pixmap1.width()) / 2;
//    int y = (h - pixmap1.height()) / 2;
//    painter->drawPixmap(x, y, alphaPixmap);

//    alpha = 255 * (factor);
//    alphaPixmap.fill(Qt::transparent);
//    QPainter p2(&alphaPixmap);
//    p2.setCompositionMode(QPainter::CompositionMode_Source);
//    p2.drawPixmap(0, 0, pixmap2);
//    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
//    p2.fillRect(alphaPixmap.rect(), QColor(0, 0, 0, alpha));
//    p2.end();

//    painter->drawPixmap(x, y, alphaPixmap);
//}

//void ImageAnimation::blindsEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
//{
//    int i, n, w, h, x1, y1, x2, y2, dh, ddh;

//    w = rect.width();
//    h = rect.height();
//    x1 = (w - pixmap1.width()) / 2;
//    y1 = (h - pixmap1.height()) / 2;
//    x2 = (w - pixmap2.width()) / 2;
//    y2 = (h - pixmap2.height()) / 2;

//    painter->drawPixmap(x1, y1, pixmap1);

//    n = 10;
//    dh = pixmap2.height() / n;
//    ddh = factor * dh;
//    if (ddh < 1) {
//        ddh = 1;
//    }

//    for(i = 0; i < n; i++) {
//        painter->drawPixmap(x2, y2 + i * dh, pixmap2, 0, i * dh, pixmap2.width(), ddh);
//    }
//}

//void ImageAnimation::flipRightToLeft(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
//{
//    int x1, y1, x2, y2, w, h;
//    float rot;
//    QTransform trans;

//    w = rect.width();
//    h = rect.height();
//    x1 = (w - pixmap1.width()) / 2;
//    y1 = (h - pixmap1.height()) / 2;
//    x2 = (w - pixmap2.width()) / 2;
//    y2 = (h - pixmap2.height()) / 2;

//    rot = factor * 90.0f;
//    trans.translate(w * (1 - factor), h / 2);
//    trans.rotate(rot, Qt::YAxis);
//    trans.translate(-w, -h / 2);

//    painter->setTransform(trans);
//    painter->drawPixmap(x1, y1, pixmap1);
//    painter->resetTransform();

//    trans.reset();
//    rot = 90 * (factor - 1);
//    trans.translate(w * (1 - factor), h / 2);
//    trans.rotate(rot, Qt::YAxis);
//    trans.translate(0, -h / 2);

//    painter->setTransform(trans);
//    painter->drawPixmap(x2, y2, pixmap2);
//    painter->resetTransform();
//}

//void ImageAnimation::outsideToInside(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
//{
//    int   w, h, x1, y1, x2, y2, x3, y3, dh, ddh;

//    w = rect.width();
//    h = rect.height();
//    x1 = (w - pixmap1.width()) / 2;
//    y1 = (h - pixmap1.height()) / 2;
//    painter->drawPixmap(x1, y1, pixmap1);

//    dh = pixmap2.height() / 2;
//    ddh = factor * dh;
//    if (ddh < 1) {
//        ddh = 1;
//    }

//    x2 = (w - pixmap2.width()) / 2;
//    y2 = (h - pixmap2.height()) / 2;
//    painter->drawPixmap(x2, y2, pixmap2, 0, 0, pixmap2.width(), ddh);

//    x3 = (w - pixmap2.width()) / 2;
//    y3 =  dh * (1.0f - factor) + h / 2;
//    if(y3 != h / 2) {
//        y3 += 1;
//    }

//    painter->drawPixmap(x3, y3, pixmap2, 0, pixmap2.height() - ddh, pixmap2.width(), ddh);
//}

//void ImageAnimation::moveLeftToRightEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2)
//{
//    int x, y, w, h, x1, y1, x2, y2;

//    w = rect.width();
//    h = rect.height();
//    x1 = (w - pixmap1.width()) / 2;
//    y1 = (h - pixmap1.height()) / 2;
//    x2 = (w - pixmap2.width()) / 2;
//    y2 = (h - pixmap2.height()) / 2;

//    x = x1 + w * factor;
//    y = y1;
//    painter->drawPixmap(x, y, pixmap1);

//    x = x2 + w * (factor - 1);
//    y = y2;
//    painter->drawPixmap(x, y, pixmap2);
//}
