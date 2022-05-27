#include "HDrawHelper.h"
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QScreen>
#include <QtSvg/QSvgRenderer>
#include <QtWidgets/QApplication>

HE_BEGIN_NAMESPACE

void calcFirstControlPoints(double *&result, const double *rhs, int n)
{
    int i;
    double *temp = new double[n];
    double b = 2.0;
    result = new double[n];
    result[0] = rhs[0] / b;

    for (i = 1; i < n; i++)
    {
        temp[i] = 1 / b;
        b = (i < n - 1 ? 4.0 : 3.5) - temp[i];
        result[i] = (rhs[i] - result[i - 1]) / b;
    }

    for (i = 1; i < n; i++)
        result[n - i - 1] -= temp[n - i] * result[n - i];

    delete[] temp;
}

void calcControlPoints(const QVector<QPointF> &datas, QVector<QPointF> &ctrlPt1, QVector<QPointF> &ctrlPt2)
{
    auto i = 0;
    auto n = datas.size() - 1;
    ctrlPt1.resize(n);
    ctrlPt2.resize(n);

    if (n == 1)
    {
        ctrlPt1[0] = (2 * datas[0] + datas[1]) / 3;
        ctrlPt2[0] = 2 * ctrlPt1[0] - datas[0];
        return;
    }

    double *xs = 0;
    double *ys = 0;
    double *rhsx = new double[n];
    double *rhsy = new double[n];
    for (i = 1; i < n - 1; i++)
    {
        rhsx[i] = 4 * datas[i].x() + 2 * datas[i + 1].x();
        rhsy[i] = 4 * datas[i].y() + 2 * datas[i + 1].y();
    }

    rhsx[0] = datas[0].x() + 2 * datas[1].x();
    rhsx[n - 1] = (8 * datas[n - 1].x() + datas[n].x()) / 2.0;
    rhsy[0] = datas[0].y() + 2 * datas[1].y();
    rhsy[n - 1] = (8 * datas[n - 1].y() + datas[n].y()) / 2.0;

    calcFirstControlPoints(xs, rhsx, n);
    calcFirstControlPoints(ys, rhsy, n);

    for (int i = 0; i < n; i++)
    {
        ctrlPt1[i] = QPointF(xs[i], ys[i]);
        if (i < n - 1)
            ctrlPt2[i] = QPointF(2 * datas[i + 1].x() - xs[i + 1], 2 * datas[i + 1].y() - ys[i + 1]);
        else
            ctrlPt2[i] = QPointF((datas[n].x() + xs[n - 1]) / 2, (datas[n].y() + ys[n - 1]) / 2);
    }

    delete xs;
    delete ys;
    delete[] rhsx;
    delete[] rhsy;
}

void HDrawHelper::drawOverlay(QPainter *painter, double radius, QColor color)
{
    QPainterPath smallCircle, bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);
    auto gradient = QLinearGradient(0, -radius / 2, 0, 0);
    color.setAlpha(100);
    gradient.setColorAt(0.0, color);
    color.setAlpha(30);
    gradient.setColorAt(1.0, color);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->rotate(-20);
    painter->drawPath(smallCircle - bigCircle);
    painter->restore();
}

void HDrawHelper::drawCrosshair(QPainter *painter, QPointF point, int width, const QColor &color)
{
    painter->save();
    painter->setPen(QPen(color, width));
    painter->drawLine(point - QPointF(0, -width * 3),  point - QPointF(0, -width));
    painter->drawLine(point - QPointF(0,  width * 3),  point - QPointF(0,  width));
    painter->drawLine(point - QPointF(-width * 3, 0),  point - QPointF(-width, 0));
    painter->drawLine(point - QPointF( width * 3, 0),  point - QPointF( width, 0));
    painter->restore();
}

void HDrawHelper::drawCrossCursor(QPainter *painter, QPointF point, int size, const QColor &color)
{
    auto text = QString("+");
    auto font = painter->font();
    font.setPixelSize(size);
    auto fm = QFontMetrics(font);
    QPainterPath path;
    path.addText(point - QPointF(fm.width(text) / 2.0, -fm.height() / 4.0), font, text);

    painter->save();
    painter->setPen(color);
    painter->drawPath(path);
    painter->restore();
}

QImage HDrawHelper::createTiledImage(int size, const QColor &color1, const QColor &color2)
{
    auto image = QImage(size * 2, size * 2, QImage::Format_ARGB32);
    image.fill(color1);

    QPainter painter(&image);
    painter.fillRect(0, 0, size, size, color2);
    painter.fillRect(size, size, size, size, color2);
    return image;
}

QImage HDrawHelper::createCrossImage(QSize size, const QPen &pen)
{
    QPainterPath path;
    path.moveTo(0, size.height() / 2.0);
    path.lineTo(size.width(), size.height() / 2.0);
    path.moveTo(size.width() / 2.0, 0);
    path.lineTo(size.width() / 2.0, size.height());

    auto image = QImage(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
    return image;
}

QImage HDrawHelper::createFontImage(const QFont &font, const QChar &c, QSize size, const QPen &pen, int flags)
{
    auto image = QImage(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(image.rect(), flags, c);
    return image;
}

QPixmap HDrawHelper::loadSvgToPixmap(const QString &fileName, QSize size)
{
    auto ratio = QApplication::primaryScreen()->devicePixelRatio();
    auto pixmap = QPixmap(size * ratio);
    pixmap.fill(Qt::transparent);

    QSvgRenderer renderer(fileName);
    QPainter painter(&pixmap);
    renderer.render(&painter);
    pixmap.setDevicePixelRatio(ratio);
    return pixmap;
}

QFont HDrawHelper::adjustFontSize(QPainter *painter, const QString &text, double width)
{
    auto font = painter->font();
    font.setPointSize(10);
    auto fm = QFontMetricsF(font);
    auto textWidth = fm.width(text);
    font.setPointSizeF(font.pointSize() * width / textWidth);
    return font;
}
// 采用Qt原生方法不做任何处理
QPainterPath HDrawHelper::createSmoothCurve(const QVector<QPointF> &points)
{
    QPainterPath path;
    auto count = points.count();
    if (count == 0)
        return path;

    path.moveTo(points.first());
    for (int i = 0; i < count - 1; i++)
    {
        // 控制点的 x 坐标为 sp 与 ep 的 x 坐标和的一半
        // 第一个控制点 c1 的 y 坐标为起始点 sp 的 y 坐标
        // 第二个控制点 c2 的 y 坐标为结束点 ep 的 y 坐标
        auto sp = points.at(i);
        auto ep = points.at(i + 1);
        auto c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
        auto c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
        path.cubicTo(c1, c2, ep);
    }

    return path;
}

QPainterPath HDrawHelper::createSmoothCurve2(const QVector<QPointF> &points)
{
    QPainterPath path;
    int len = points.size();
    if (len < 2)
        return path;

    QVector<QPointF> ctrlPt1, ctrlPt2;
    calcControlPoints(points, ctrlPt1, ctrlPt2);

    path.moveTo(points.first());
    for (int i = 0; i < len - 1; i++)
        path.cubicTo(ctrlPt1[i], ctrlPt2[i], points[i + 1]);

    return path;

}

HE_END_NAMESPACE
