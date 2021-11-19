#include "HMath.h"
#include <QtCore/QtMath>
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

double HMath::sum(QVector<double> value)
{
    if (value.size() < 1)
        return 0.0;
    auto sum = 0.0;
    for (auto v : value)
        sum += v;
    return sum;
}

double HMath::average(QVector<double> value)
{
    if (value.size() < 1)
        return 0.0;
    return sum(value) / value.size();
}

double HMath::interpolate(double x, double x1, double y1, double x2, double y2)
{
    return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}

double HMath::interpolate(double x, QPointF p1, QPointF p2)
{
    return interpolate(x, p1.x(), p1.y(), p2.x(), p2.y());
}

double HMath::interpolate(double x, QPolygonF poly)
{
    if (poly.size() < 2)
        return 0;

    int i;
    for (i = 1; i < poly.size() - 1; i++)
    {
        if (x <= poly[i].x())
            break;
    }
    return interpolate(x, poly[i - 1], poly[i]);
}

QPolygonF HMath::interpolate(QPolygonF poly, double x1, double x2, double interval)
{
    int i,j,n;
    double x, y;
    QPolygonF result;

    if (poly.size() < 2)
        return result;

    if (x2 < x1)
        qSwap(x1, x2);

    n = ceil((x2 - x1) / interval + 1);
    for (i = 0, j = 1; i < n; i++)
    {
        x = x1 + i * interval;
        for (; x > poly[j].x() && j < poly.size() - 1; j++);
        y = interpolate(x, poly[j-1], poly[j]);
        result.append(QPointF(x, y));
    }
    return result;
}

double HMath::interpolateY(double y, QPointF p1, QPointF p2)
{
    return interpolate(y, p1.y(), p1.x(), p2.y(), p2.x());
}

double HMath::interpolateY(double y, QPolygonF poly)
{
    if (poly.size() < 2)
        return 0;

    int i;
    for (i = 1; i < poly.size() - 1; i++)
    {
        if (y <= poly[i].y())
            break;
    }
    return interpolateY(y, poly[i-1], poly[i]);
}

QPolygonF HMath::calcEllipse(QPointF center, double r, double theta, double a, double b)
{
    QPolygonF poly;
    auto theta1 = qDegreesToRadians(theta);
    for (int i = 0; i < 3600; i++)
    {
        auto theta2 = qDegreesToRadians(i * 0.1);
        auto x1 = r * a * cos(theta2);
        auto y1 = r * b * sin(theta2);
        auto x2 = x1 * cos(theta1) - y1 * sin(theta1) + center.x();
        auto y2 = x1 * sin(theta1) + y1 * cos(theta1) + center.y();
        poly << QPointF(x2, y2);
    }
    return poly;
}

//bool HMath::polyfit(QVector<QPointF> points, QVector<double> &factors)
//{
//    int i,j,k,m,n;
//    double d1,d2,c,p,g,q;
//    QVector<double> B,S,T;

//    m = points.size();
//    n = factors.size();
//    if (n < 0 || m < 1)
//        return false;

//    if (n > m)
//    {
//        n = m;
//        factors.resize(n);
//    }

//    B.resize(m);
//    S.resize(m);
//    T.resize(m);

//    B[0] = 1;
//    d1 = m;
//    p = 0;
//    c = 0;
//    q = 0;

//    for (i = 0; i < m; i++)
//    {
//        p += points[i].x();
//        c += points[i].y();
//    }
//    c /= d1;
//    p /= d1;
//    factors[0] = c * B[0];

//    if (n > 1)
//    {
//        T[1] = 1;
//        T[0] = -p;
//        d2 = 0;
//        c = 0;
//        g = 0;
//        for (i = 0; i < m; i++)
//        {
//            q = points[i].x() - p;
//            d2 += q * q;
//            c += points[i].y() * q;
//            g += points[i].x() * q * q;
//        }
//        c = c / d2;
//        p = g / d2;
//        q = d2 / d1;
//        d1 = d2;
//        factors[1] = c * T[1];
//        factors[0] = c * T[0] + factors[0];
//    }

//    for (j = 2; j < n; j++)
//    {
//        S[j] = T[j-1];
//        S[j-1] = -p * T[j-1] + T[j-2];
//        if (j >= 3)
//        {
//            for (k = j-2; k >= 1; k--)
//                S[k] = -p * T[k] + T[k-1] - q * B[k];
//        }
//        S[0] = -p * T[0] - q * B[0];
//        d2 = 0;
//        c = 0;
//        g = 0;
//        for (i = 0; i < m; i++)
//        {
//            q = S[j];
//            for (k = j-1; k >= 0; k--)
//                q = q * points[i].x() + S[k];
//            d2 += q * q;
//            c += points[i].y() * q;
//            g += points[i].x() * q * q;
//        }
//        c = c/d2;
//        p = g/d2;
//        q = d2/d1;
//        d1 = d2;
//        factors[j] = c * S[j];
//        T[j] = S[j];
//        for (k = j-1; k >= 0; k--)
//        {
//            factors[k] += c * S[k];
//            B[k] = T[k];
//            T[k] = S[k];
//        }
//    }
//    return true;
//}

HE_ALGORITHM_END_NAMESPACE
