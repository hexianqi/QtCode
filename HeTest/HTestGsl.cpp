#include "HTestGsl.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HPolynomial.h"
#include "HeAlgorithm/HLinearFitting.h"
#include "HTestChart.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtCharts/QChartView>

HE_ALGORITHM_USE_NAMESPACE

QPolygonF readCieDay()
{
    int i,n;
    QString str;

    QFile file(":/dat/CIE_DAY.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QPolygonF poly;
    double x,y,t1,t2;

    in >> str >> n;
    str = in.readLine();
    str = in.readLine();

    for (i = 0; i < n; i++)
    {
        in >> x >> y >> t1 >> t2;
        poly << QPointF(x,y);
    }
    file.close();
    return poly;
}

HTestGsl::HTestGsl()
{
}

HTestGsl::~HTestGsl()
{
}

/* polynomial: P(x) =  1 + 0.5 * x + 0.3 * x^2  */
void HTestGsl::polyEval()
{
    QVector<double> a;
    a << 1.0 << 0.5 << 0.3;
    auto x = 0.5;
    auto y = HPolynomial::eval(a, x);
    qDebug() << __FUNCTION__;
    qDebug() << "P(x) =  1 + 0.5 * x + 0.3 * x^2";
    qDebug() << "P(0.5) = " << y;
}

/* polynomial: P(x) =  -1 + x^5 */
void HTestGsl::polySolve()
{
    QVector<double> a;
    a << -1 << 0 << 0 << 0 << 0 << 1;
    auto r = HPolynomial::solveComplex(a);
    qDebug() << __FUNCTION__;
    qDebug() << "P(x) =  -1 + x^5";
    for (int i = 0; i < r.size(); i++)
        qDebug() << QString("z%1 = %2 + %3 * i").arg(i).arg(r[i].x()).arg(r[i].y());
}

QPolygonF HTestGsl::specialAirAi()
{
//    QPolygonF r;
//    for (int i = -100; i <= 100; i++)
//        r << QPointF(i, _special->airyAi(i));
//    return r;
}

QPolygonF HTestGsl::specialAirBi()
{
//    QPolygonF r;
//    for (int i = -100; i < 0; i++)
//        r << QPointF(i, _special->airyBi(i));
//    return r;
}

QWidget *HTestGsl::interpEval()
{
    auto p1 = readCieDay();
    auto p2 = HInterp::eval(p1, p1.first().x() - 10, p1.last().x() + 10, 0.1, HInterpType::Cspline);
    return HTestChart::diffChart(p1, p2);
}

QWidget *HTestGsl::linearFitting()
{
    QPolygonF p1;
    QList<QPolygonF> list;

    p1 << QPointF(1970, 12) << QPointF(1980, 11) << QPointF(1990, 14) << QPointF(2000, 13);
    list << p1;
    for (int j = 0; j < 4; j++)
    {
        double chisq, xf, yf, yf_err;
        QPolygonF p2, p3, p4;
        QVector<double> c, cov, w;

        w.fill(1, 4);
        w[j] = 10;
        HLinearFitting::wlinear(p1, w, c, cov, &chisq);

        for (int i = -30; i < 130; i++)
        {
            xf = p1.first().x() + (p1.last().x() - p1.first().x()) * i / 100.0;
            HLinearFitting::linearEst(xf, c, cov, &yf, &yf_err);
            p2 << QPointF(xf, yf);
            p3 << QPointF(xf, yf + yf_err);
            p4 << QPointF(xf, yf - yf_err);
        }
        list << p2 << p3 << p4;

        qDebug() << __FUNCTION__;
        qDebug() << QString("best fit: Y = %1 + %2 * x").arg(c[0]).arg(c[1]);
        qDebug() << QString("chisq = %1").arg(chisq);
        qDebug() << QString("covariance matrix:");
        qDebug() << QString("[ %1, %2").arg(cov[0]).arg(cov[1]);
        qDebug() << QString("  %1, %2 ]").arg(cov[1]).arg(cov[2]);
    }
    return HTestChart::lineChart(list);
}
