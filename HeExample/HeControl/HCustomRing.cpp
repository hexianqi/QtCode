#include "HCustomRing_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HCustomRing::HCustomRing(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HCustomRingPrivate)
{
}

HCustomRing::HCustomRing(HCustomRingPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HCustomRing::~HCustomRing()
{
}

bool HCustomRing::isShowTitle() const
{
    return d_ptr->showTitle;
}

QString HCustomRing::title() const
{
    return d_ptr->title;
}

int HCustomRing::titleHeight() const
{
    return d_ptr->titleHeight;
}

int HCustomRing::titleFontSize() const
{
    return d_ptr->titleFontSize;
}

bool HCustomRing::isShowLegend() const
{
    return d_ptr->showLegend;
}

int HCustomRing::legendHeight() const
{
    return d_ptr->legendHeight;
}

int HCustomRing::legendFontSize() const
{
    return d_ptr->legendFontSize;
}

QColor HCustomRing::background() const
{
    return d_ptr->background;
}

QColor HCustomRing::textColor() const
{
    return d_ptr->textColor;
}

QColor HCustomRing::highColor() const
{
    return d_ptr->highColor;
}

QColor HCustomRing::flagColor() const
{
    return d_ptr->flagColor;
}

QColor HCustomRing::outerCircleColor() const
{
    return d_ptr->outerCircleColor;
}

QColor HCustomRing::innerCircleColor() const
{
    return d_ptr->innerCircleColor;
}

QColor HCustomRing::centerCircleColor() const
{
    return d_ptr->centerCircleColor;
}

QString HCustomRing::outerPieInfos() const
{
    return d_ptr->outerPieInfos;
}

QString HCustomRing::innerPieInfos() const
{
    return d_ptr->innerPieInfos;
}

void HCustomRing::setShowTitle(bool b)
{
    if (d_ptr->showTitle == b)
        return;
    d_ptr->showTitle = b;
    update();
}

void HCustomRing::setTitle(const QString &value)
{
    if (d_ptr->title == value)
        return;
    d_ptr->title = value;
    update();
}

void HCustomRing::setTitleHeight(int value)
{
    if (d_ptr->titleHeight == value)
        return;
    d_ptr->titleHeight = value;
    update();
}

void HCustomRing::setTitleFontSize(int value)
{
    if (d_ptr->titleFontSize == value)
        return;
    d_ptr->titleFontSize = value;
    update();
}

void HCustomRing::setShowLegend(bool b)
{
    if (d_ptr->showLegend == b)
        return;
    d_ptr->showLegend = b;
    update();
}

void HCustomRing::setLegendHeight(int value)
{
    if (d_ptr->legendHeight == value)
        return;
    d_ptr->legendHeight = value;
    update();
}

void HCustomRing::setLegendFontSize(int value)
{
    if (d_ptr->legendFontSize == value)
        return;
    d_ptr->legendFontSize = value;
    update();
}

void HCustomRing::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HCustomRing::setTextColor(const QColor &value)
{
    if (d_ptr->textColor == value)
        return;
    d_ptr->textColor = value;
    update();
}

void HCustomRing::setHighColor(const QColor &value)
{
    if (d_ptr->highColor == value)
        return;
    d_ptr->highColor = value;
    update();
}

void HCustomRing::setFlagColor(const QColor &value)
{
    if (d_ptr->flagColor == value)
        return;
    d_ptr->flagColor = value;
    update();
}

void HCustomRing::setOuterCircleColor(const QColor &value)
{
    if (d_ptr->outerCircleColor == value)
        return;
    d_ptr->outerCircleColor = value;
    update();
}

void HCustomRing::setInnerCircleColor(const QColor &value)
{
    if (d_ptr->innerCircleColor == value)
        return;
    d_ptr->innerCircleColor = value;
    update();
}

void HCustomRing::setCenterCircleColor(const QColor &value)
{
    if (d_ptr->centerCircleColor == value)
        return;
    d_ptr->centerCircleColor = value;
    update();
}

void HCustomRing::setOuterPieInfos(const QString &value)
{
    if (d_ptr->outerPieInfos == value)
        return;
    d_ptr->outerPieInfos = value;
    update();
}

void HCustomRing::setInnerPieInfos(const QString &value)
{
    if (d_ptr->innerPieInfos == value)
        return;
    d_ptr->innerPieInfos = value;
    update();
}

//void CustomRing::mouseMoveEvent(QMouseEvent *event)
//{
//    //通过绘制路径的contains方法判断鼠标是否在对应区域内
//    bool contains = false;
//    for (int i = 0; i < inPieInfo.size(); i++) {
//        if (inPieInfo.at(i).path.contains(event->pos())) {
//            inPieInfo[i].offset = 5;
//            contains = true;
//        } else {
//            if (inPieInfo.at(i).offset != 0) {
//                contains = true;
//            }

//            inPieInfo[i].offset = 0;
//        }
//    }

//    //优先绘制内圆偏移
//    if (contains) {
//        for (int i = 0; i < outPieInfo.size(); i++) {
//            outPieInfo[i].offset = 0;
//        }

//        update();
//        return;
//    }

//    for (int i = 0; i < outPieInfo.size(); i++) {
//        if (outPieInfo.at(i).path.contains(event->pos())) {
//            outPieInfo[i].offset = 5;
//            contains = true;
//        } else {
//            if (outPieInfo.at(i).offset != 0) {
//                contains = true;
//            }

//            outPieInfo[i].offset = 0;
//        }
//    }

//    if (contains) {
//        update();
//    }
//}

//void CustomRing::paintEvent(QPaintEvent *)
//{
//    //绘制准备工作,启用反锯齿
//    QPainter painter(this);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

//    int titleHeight = showTitle ? this->titleHeight : 0;
//    int legendHeight = showLegend ? this->legendHeight : 0;
//    QRect rect(0, titleHeight, this->width(), this->height() - titleHeight - legendHeight);
//    int side = qMin(rect.width(), rect.height());
//    qreal scale = side / 200.0;

//    //绘制背景
//    drawBg(&painter);

//    //平移坐标轴中心,等比例缩放
//    painter.save();
//    painter.translate(rect.center());
//    painter.scale(scale, scale);

//    //绘制外圆背景
//    drawOutCircle(&painter);
//    //绘制外层饼图
//    drawOutPie(&painter, scale, rect.center());
//    //绘制中间圆
//    drawMidCircle(&painter);
//    //绘制里层饼图
//    drawInPie(&painter, scale, rect.center());
//    //绘制里边圆
//    drawInCircle(&painter);

//    painter.restore();

//    //重新等比例缩放,绘制文字,文字放在后面绘制是为了不被圆遮挡
//    painter.scale(scale, scale);

//    //绘制标题
//    if (showTitle) {
//        drawTitle(&painter);
//    }

//    //绘制图例文字
//    if (showLegend) {
//        drawLegendText(&painter, scale);
//    }
//}

//void CustomRing::drawBg(QPainter *painter)
//{
//    painter->save();
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(bgColor);
//    painter->drawRoundedRect(this->rect(), 5, 5);
//    painter->restore();
//}

//void CustomRing::drawOutCircle(QPainter *painter)
//{
//    int radius = 90;
//    painter->save();
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(outCircleColor);
//    painter->drawEllipse(QPoint(0, 0), radius, radius);
//    painter->restore();
//}

//void CustomRing::drawMidCircle(QPainter *painter)
//{
//    int radius = 50;
//    painter->save();
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(midCircleColor);
//    painter->drawEllipse(QPoint(0, 0), radius, radius);
//    painter->restore();
//}

//void CustomRing::drawInCircle(QPainter *painter)
//{
//    int radius = 10;
//    painter->save();
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(inCircleColor);
//    painter->drawEllipse(QPoint(0, 0), radius, radius);
//    painter->restore();
//}

HE_CONTROL_END_NAMESPACE
